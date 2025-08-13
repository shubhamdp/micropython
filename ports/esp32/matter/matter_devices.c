#include "py/obj.h"

// lights
static mp_obj_t matter_device_on_off_light_create();
static mp_obj_t matter_device_dimmable_light_create();
static mp_obj_t matter_device_color_temperature_light_create();
static mp_obj_t matter_device_extended_color_light_create();
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_on_off_light_create_obj, matter_device_on_off_light_create);
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_dimmable_light_create_obj, matter_device_dimmable_light_create);
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_color_temperature_light_create_obj, matter_device_color_temperature_light_create);
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_extended_color_light_create_obj, matter_device_extended_color_light_create);

// switches
static mp_obj_t matter_device_on_off_switch_create();
static mp_obj_t matter_device_dimmer_switch_create();
static mp_obj_t matter_device_color_dimmer_switch_create();
static mp_obj_t matter_device_generic_switch_create();
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_on_off_switch_create_obj, matter_device_on_off_switch_create);
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_dimmer_switch_create_obj, matter_device_dimmer_switch_create);
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_color_dimmer_switch_create_obj, matter_device_color_dimmer_switch_create);
static MP_DEFINE_CONST_FUN_OBJ_0(matter_device_generic_switch_create_obj, matter_device_generic_switch_create);

static const mp_rom_map_elem_t matter_device_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_on_off_light_create), MP_ROM_PTR(&matter_device_on_off_light_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_dimmable_light_create), MP_ROM_PTR(&matter_device_dimmable_light_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_temperature_light_create), MP_ROM_PTR(&matter_device_color_temperature_light_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_extended_color_light_create), MP_ROM_PTR(&matter_device_extended_color_light_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_on_off_switch_create), MP_ROM_PTR(&matter_device_on_off_switch_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_dimmer_switch_create), MP_ROM_PTR(&matter_device_dimmer_switch_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_dimmer_switch_create), MP_ROM_PTR(&matter_device_color_dimmer_switch_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_generic_switch_create), MP_ROM_PTR(&matter_device_generic_switch_create_obj) },
};
static MP_DEFINE_CONST_DICT(matter_device_module_globals, matter_device_module_globals_table);

const mp_obj_module_t matter_device_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&matter_device_module_globals,
};