
// Declare MicroPython C functions to avoid C++ name mangling
extern "C" {
#include "py/obj.h"
#include "py/runtime.h"
}

#include <nvs_flash.h>
#include <esp_err.h>
#include <esp_matter.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include <stdint.h>

using namespace esp_matter;
using namespace esp_matter::attribute;
using namespace esp_matter::endpoint;

static const char *TAG = "matter";

// Generic callback item - just a Python function + arguments
typedef struct {
    mp_obj_t callback_function;    // The Python function to call
    uint8_t num_args;             // Number of arguments
    mp_obj_t args[];              // Variable-length array of arguments
} generic_callback_item_t;    

static QueueHandle_t callback_queue = NULL;
static mp_sched_node_t callback_node1;
static mp_sched_node_t callback_node2;
static mp_sched_node_t callback_node3;

// Simple storage for the attribute callback
static mp_obj_t attribute_callback = mp_const_none;
// for identify callback
static mp_obj_t identify_callback = mp_const_none;
// event callback
static mp_obj_t event_callback = mp_const_none;

// Generic scheduled callback that processes all queued items  
static void process_generic_callbacks(mp_sched_node_t *node) {
    // Process all queued callbacks - receive pointer to allocated callback item
    uintptr_t item_ptr;
    while (xQueueReceive(callback_queue, &item_ptr, 0) == pdTRUE) {
        generic_callback_item_t *item = (generic_callback_item_t*)item_ptr;
        
        if (item->callback_function != mp_const_none) {
            // Call the Python function with the provided arguments
            mp_call_function_n_kw(item->callback_function, item->num_args, 0, item->args);
        }    

        // Free the allocated callback item
        free(item);
    }    
}

// Ultra-generic function to schedule any callback with any arguments
static esp_err_t schedule_generic_callback(mp_obj_t callback_function, uint8_t num_args, mp_obj_t *args)
{
    ESP_LOGE(TAG, "Scheduling generic callback");

    if (callback_queue == NULL) {
        ESP_LOGE(TAG, "Callback queue not initialized");
        return ESP_FAIL;
    }    
    
    if (callback_function == mp_const_none) {
        return ESP_OK; // No callback registered, that's fine
    }
    
    // Allocate memory for the callback item + arguments
    size_t item_size = sizeof(generic_callback_item_t) + (num_args * sizeof(mp_obj_t));
    generic_callback_item_t *item = (generic_callback_item_t*)malloc(item_size);
    if (item == NULL) {
        ESP_LOGE(TAG, "Failed to allocate callback item");
        return ESP_FAIL;
    }    
    
    // Fill in the callback item
    item->callback_function = callback_function;
    item->num_args = num_args;
    for (uint8_t i = 0; i < num_args; i++) {
        item->args[i] = args[i];
    }    
    
    // Queue the pointer to the item (not the item itself)
    uintptr_t item_ptr = (uintptr_t)item;
    BaseType_t result = xQueueSend(callback_queue, &item_ptr, 0);
    if (result != pdTRUE) {
        ESP_LOGW(TAG, "Failed to queue generic callback");
        free(item);
        return ESP_FAIL;
    }    
    
    // Schedule processing (safe to call multiple times)
    if (callback_function == identify_callback) {
        bool result = mp_sched_schedule_node(&callback_node1, process_generic_callbacks);
        if (!result) {
            ESP_LOGE(TAG, "Failed to schedule generic callback");
            return ESP_FAIL;
        }    
    } else if (callback_function == event_callback) {
        bool result = mp_sched_schedule_node(&callback_node2, process_generic_callbacks);
        if (!result) {
            ESP_LOGE(TAG, "Failed to schedule generic callback");
            return ESP_FAIL;    
        }
    } else if (callback_function == attribute_callback) {
        bool result = mp_sched_schedule_node(&callback_node3, process_generic_callbacks);
        if (!result) {
            ESP_LOGE(TAG, "Failed to schedule generic callback");
            return ESP_FAIL;
        }    
    }    
    return ESP_OK;
}    

static void app_event_cb(const ChipDeviceEvent *event, intptr_t arg)
{
    if (event_callback == mp_const_none) {
        return;
    }

    mp_obj_t args[1] = { mp_obj_new_int(event->Type) };
    schedule_generic_callback(event_callback, 1, args);
}

// may be for enum/class stuff, we can write the matter.py wrappers which uses this base layer and introduce the
// very high level interface to users which they can look at for reference.

static esp_err_t app_identification_cb(identification::callback_type_t type, uint16_t endpoint_id, uint8_t effect_id,
                                       uint8_t effect_variant, void *priv_data)
{
    mp_obj_t args[4] = {
        mp_obj_new_int(type),
        mp_obj_new_int(endpoint_id),
        mp_obj_new_int(effect_id),
        mp_obj_new_int(effect_variant)
    };
    schedule_generic_callback(identify_callback, 4, args);

    return ESP_OK;
}

static mp_obj_t esp_matter_val_to_mp_obj(const esp_matter_attr_val_t *val)
{
    switch (val->type) {
        case ESP_MATTER_VAL_TYPE_BOOLEAN:
            return mp_obj_new_bool(val->val.b);
        case ESP_MATTER_VAL_TYPE_INT8:
            return mp_obj_new_int(val->val.i8);
        case ESP_MATTER_VAL_TYPE_UINT8:
            return mp_obj_new_int(val->val.u8);
        case ESP_MATTER_VAL_TYPE_INT16:
            return mp_obj_new_int(val->val.i16);
        case ESP_MATTER_VAL_TYPE_UINT16:
            return mp_obj_new_int(val->val.u16);
        case ESP_MATTER_VAL_TYPE_INT32:
            return mp_obj_new_int(val->val.i32);
        case ESP_MATTER_VAL_TYPE_UINT32:
            return mp_obj_new_int_from_uint(val->val.u32);
        case ESP_MATTER_VAL_TYPE_OCTET_STRING:
            return mp_obj_new_str((const char *)val->val.p, val->val.a.s);  // assume val.p points to string
        case ESP_MATTER_VAL_TYPE_ARRAY:
            return mp_obj_new_bytes(val->val.a.b, val->val.a.s);
        default:
            ESP_LOGE(TAG, "Unknown attribute value type: %d", val->type);
            return mp_const_none;
    }
}

// Initialize the callback system
static esp_err_t init_callback_system()
{
    // Create queue for callback pointers (can hold 20 pointers)
    callback_queue = xQueueCreate(20, sizeof(uintptr_t));
    if (callback_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create callback queue");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Generic callback system initialized");
    return ESP_OK;
}

static esp_err_t app_attribute_update_cb(attribute::callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id,
                                         uint32_t attribute_id, esp_matter_attr_val_t *val, void *priv_data)
{
    if (type == POST_UPDATE) {
        return ESP_OK;
    }

    if (attribute_callback == mp_const_none) {
        ESP_LOGE(TAG, "Python attribute callback is not set");
        return ESP_OK;
    }

    ESP_LOGE(TAG, "PRE_UPDATE on attribute path --> %u:%" PRIu32 ":%" PRIu32, endpoint_id, cluster_id, attribute_id);

    // Prepare arguments for the callback
    mp_obj_t args[4] = {
        mp_obj_new_int(endpoint_id),
        mp_obj_new_int(cluster_id),
        mp_obj_new_int(attribute_id),
        esp_matter_val_to_mp_obj(val)
    };

    // Schedule the callback with 4 arguments
    schedule_generic_callback(attribute_callback, 4, args);

    return ESP_OK;
}

// Very very generic way to create a matter certifiable device
template <typename T>
using create_func_t = endpoint_t* (*)(node_t *node, T *config, uint8_t flags, void *priv_data);

// On-Off Light Device
template <typename T>
static mp_obj_t matter_device_create(T *config, create_func_t<T> create_func)
{
    node_t *node = esp_matter::node::get();
    if (node == nullptr) {
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Matter node not initialized. Call matter.start() first."));
    }

    endpoint_t *endpoint = create_func(node, config, 0, nullptr);
    if (endpoint == nullptr) {
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Failed to create on-off light endpoint"));
    }

    return mp_obj_new_int(endpoint::get_id(endpoint));
}

#ifdef __cplusplus
extern "C" {
#endif

// Lights
mp_obj_t matter_device_on_off_light_create()
{
    on_off_light::config_t config;
    return matter_device_create<on_off_light::config_t>(&config, on_off_light::create);
}

mp_obj_t matter_device_dimmable_light_create()
{
    dimmable_light::config_t config;
    return matter_device_create<dimmable_light::config_t>(&config, dimmable_light::create);
}

mp_obj_t matter_device_color_temperature_light_create()
{
    color_temperature_light::config_t config;
    return matter_device_create<color_temperature_light::config_t>(&config, color_temperature_light::create);
}

mp_obj_t matter_device_extended_color_light_create()
{
    extended_color_light::config_t config;
    return matter_device_create<extended_color_light::config_t>(&config, extended_color_light::create);
}

// Switches
mp_obj_t matter_device_on_off_switch_create()
{
    on_off_switch::config_t config;
    return matter_device_create<on_off_switch::config_t>(&config, on_off_switch::create);
}

mp_obj_t matter_device_dimmer_switch_create()
{
    dimmer_switch::config_t config;
    return matter_device_create<dimmer_switch::config_t>(&config, dimmer_switch::create);
}

mp_obj_t matter_device_color_dimmer_switch_create()
{
    color_dimmer_switch::config_t config;
    return matter_device_create<color_dimmer_switch::config_t>(&config, color_dimmer_switch::create);
}

mp_obj_t matter_device_generic_switch_create()
{
    generic_switch::config_t config;
    return matter_device_create<generic_switch::config_t>(&config, generic_switch::create);
}

mp_obj_t matter_node_create(mp_obj_t py_attribute_cb_in, mp_obj_t py_identify_cb_in)
{
    if (!mp_obj_is_callable(py_attribute_cb_in)) {
        return mp_obj_new_int(ESP_ERR_INVALID_ARG);
    }
    if (!mp_obj_is_callable(py_identify_cb_in)) {
        return mp_obj_new_int(ESP_ERR_INVALID_ARG);
    }

    nvs_flash_init();

    // Initialize the callback system
    esp_err_t ret = init_callback_system();
    if (ret != ESP_OK) {
        return mp_obj_new_int(ret);
    }

    attribute_callback = py_attribute_cb_in;
    identify_callback = py_identify_cb_in;

    ESP_LOGI(TAG, "Initialized Matter with python attribute callback");

    node::config_t node_config;
    node_t *node = node::create(&node_config, app_attribute_update_cb, app_identification_cb);

    if (!node) {
        ESP_LOGE(TAG, "Failed to create node");
        return mp_obj_new_int(ESP_FAIL);
    }
    return mp_obj_new_int(ESP_OK);
}

mp_obj_t matter_start(mp_obj_t py_event_cb_in)
{
    if (!mp_obj_is_callable(py_event_cb_in)) {
        return mp_obj_new_int(ESP_ERR_INVALID_ARG);
    }

    if (node::get() == nullptr) {
        ESP_LOGE(TAG, "Matter node not initialized. Call matter.node_create() first.");
        return mp_obj_new_int(ESP_ERR_INVALID_STATE);
    }

    event_callback = py_event_cb_in;

    esp_err_t err = esp_matter::start(app_event_cb);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start Matter stack");
        return mp_obj_new_int(err);
    }
    return mp_obj_new_int(ESP_OK);
}

#ifdef __cplusplus
} // extern "C"
#endif
