#include "py/runtime.h"
#include "py/obj.h"

#include "esp_err.h"

#include "matter/matter_flags.h"

// External C function declaration from matter_main.c
extern esp_err_t matter_init(void);

// Matter start function
static mp_obj_t matter_start(void) {
    esp_err_t err = matter_init();
    if (err != ESP_OK) {
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Failed to initialize Matter"));
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(matter_start_obj, matter_start);

// Define module globals table
static const mp_rom_map_elem_t matter_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_matter) },
    { MP_ROM_QSTR(MP_QSTR_start), MP_ROM_PTR(&matter_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_EVENT_TYPES), MP_ROM_PTR(&matter_event_type_dict) },
    { MP_ROM_QSTR(MP_QSTR_ENDPOINT_FLAGS), MP_ROM_PTR(&matter_endpoint_flags_dict) },
    { MP_ROM_QSTR(MP_QSTR_CLUSTER_FLAGS), MP_ROM_PTR(&matter_cluster_flags_dict) },
    { MP_ROM_QSTR(MP_QSTR_ATTRIBUTE_FLAGS), MP_ROM_PTR(&matter_attribute_flags_dict) },
    { MP_ROM_QSTR(MP_QSTR_COMMAND_FLAGS), MP_ROM_PTR(&matter_command_flags_dict) },
};
static MP_DEFINE_CONST_DICT(matter_module_globals, matter_module_globals_table);

// Define module object
const mp_obj_module_t matter_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&matter_module_globals,
};

// Register the module
MP_REGISTER_MODULE(MP_QSTR_matter, matter_module); 
