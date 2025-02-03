#include "py/obj.h"
#include <esp_matter.h>

extern "C" {

// Create a type object for event types
static const mp_rom_map_elem_t matter_event_type_constants[] = {
    { MP_ROM_QSTR(MP_QSTR_COMMISSIONING_SESSION_STARTED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kCommissioningSessionStarted) },
    { MP_ROM_QSTR(MP_QSTR_COMMISSIONING_SESSION_STOPPED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kCommissioningSessionStopped) },
    { MP_ROM_QSTR(MP_QSTR_COMMISSIONING_WINDOW_OPENED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened) },
    { MP_ROM_QSTR(MP_QSTR_COMMISSIONING_WINDOW_CLOSED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kCommissioningWindowClosed) },
    { MP_ROM_QSTR(MP_QSTR_FABRIC_WILL_BE_REMOVED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kFabricWillBeRemoved) },
    { MP_ROM_QSTR(MP_QSTR_FABRIC_REMOVED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kFabricRemoved) },
    { MP_ROM_QSTR(MP_QSTR_FABRIC_COMMITTED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kFabricCommitted) },
    { MP_ROM_QSTR(MP_QSTR_FABRIC_UPDATED), MP_ROM_INT(chip::DeviceLayer::DeviceEventType::kFabricUpdated) },
};
extern MP_DEFINE_CONST_DICT(matter_event_type_dict, matter_event_type_constants);

// Create a type object for ENDPOINT_FLAGS
static const mp_rom_map_elem_t matter_endpoint_flags_constants[] = {
    { MP_ROM_QSTR(MP_QSTR_FLAG_NONE), MP_ROM_INT(esp_matter::ENDPOINT_FLAG_NONE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_DESTROYABLE), MP_ROM_INT(esp_matter::ENDPOINT_FLAG_DESTROYABLE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_BRIDGE), MP_ROM_INT(esp_matter::ENDPOINT_FLAG_BRIDGE) },
};
extern MP_DEFINE_CONST_DICT(matter_endpoint_flags_dict, matter_endpoint_flags_constants);

// Create a type object for CLUSTER_FLAGS
static const mp_rom_map_elem_t matter_cluster_flags_constants[] = {
    { MP_ROM_QSTR(MP_QSTR_FLAG_NONE), MP_ROM_INT(esp_matter::CLUSTER_FLAG_NONE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_INIT_FUNCTION), MP_ROM_INT(esp_matter::CLUSTER_FLAG_INIT_FUNCTION) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_ATTRIBUTE_CHANGED_FUNCTION), MP_ROM_INT(esp_matter::CLUSTER_FLAG_ATTRIBUTE_CHANGED_FUNCTION) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_SHUTDOWN_FUNCTION), MP_ROM_INT(esp_matter::CLUSTER_FLAG_SHUTDOWN_FUNCTION) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_PRE_ATTRIBUTE_CHANGED_FUNCTION), MP_ROM_INT(esp_matter::CLUSTER_FLAG_PRE_ATTRIBUTE_CHANGED_FUNCTION) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_SERVER), MP_ROM_INT(esp_matter::CLUSTER_FLAG_SERVER) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_CLIENT), MP_ROM_INT(esp_matter::CLUSTER_FLAG_CLIENT) },
};
extern MP_DEFINE_CONST_DICT(matter_cluster_flags_dict, matter_cluster_flags_constants);

// Create a type object for ATTRIBUTE_FLAGS
static const mp_rom_map_elem_t matter_attribute_flags_constants[] = {
    { MP_ROM_QSTR(MP_QSTR_FLAG_NONE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_NONE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_WRITABLE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_WRITABLE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_NONVOLATILE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_NONVOLATILE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_MIN_MAX), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_MIN_MAX) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_MUST_USE_TIMED_WRITE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_MUST_USE_TIMED_WRITE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_EXTERNAL_STORAGE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_EXTERNAL_STORAGE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_SINGLETON), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_SINGLETON) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_NULLABLE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_NULLABLE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_OVERRIDE), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_OVERRIDE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_DEFERRED), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_DEFERRED) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_MANAGED_INTERNALLY), MP_ROM_INT(esp_matter::ATTRIBUTE_FLAG_MANAGED_INTERNALLY) },
};
extern MP_DEFINE_CONST_DICT(matter_attribute_flags_dict, matter_attribute_flags_constants);

// Create a type object for COMMAND_FLAGS
static const mp_rom_map_elem_t matter_command_flags_constants[] = {
    { MP_ROM_QSTR(MP_QSTR_FLAG_NONE), MP_ROM_INT(esp_matter::COMMAND_FLAG_NONE) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_CUSTOM), MP_ROM_INT(esp_matter::COMMAND_FLAG_CUSTOM) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_ACCEPTED), MP_ROM_INT(esp_matter::COMMAND_FLAG_ACCEPTED) },
    { MP_ROM_QSTR(MP_QSTR_FLAG_GENERATED), MP_ROM_INT(esp_matter::COMMAND_FLAG_GENERATED) },
};
extern MP_DEFINE_CONST_DICT(matter_command_flags_dict, matter_command_flags_constants);

} // extern "C" 
