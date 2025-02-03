#pragma once

#include "py/obj.h"

#ifdef __cplusplus
extern "C" {
#endif

// Getter functions for flag dictionaries
extern const mp_obj_dict_t matter_event_type_dict;
extern const mp_obj_dict_t matter_endpoint_flags_dict;
extern const mp_obj_dict_t matter_cluster_flags_dict;
extern const mp_obj_dict_t matter_attribute_flags_dict;
extern const mp_obj_dict_t matter_command_flags_dict;

#ifdef __cplusplus
}
#endif 
