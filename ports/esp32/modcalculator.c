/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Your Name
 *
 * Permission is hereby granted...
 * [Rest of MIT license text]
 */

#include <stdio.h>
#include "py/runtime.h"
#include "py/obj.h"
#include "py/builtin.h"

// Define STATIC if not already defined
#ifndef STATIC
#define STATIC static
#endif

// Calculator functions
STATIC mp_obj_t calculator_add(mp_obj_t a_in, mp_obj_t b_in) {
    mp_int_t a = mp_obj_get_int(a_in);
    mp_int_t b = mp_obj_get_int(b_in);
    return mp_obj_new_int(a + b);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(calculator_add_obj, calculator_add);

STATIC mp_obj_t calculator_subtract(mp_obj_t a_in, mp_obj_t b_in) {
    mp_int_t a = mp_obj_get_int(a_in);
    mp_int_t b = mp_obj_get_int(b_in);
    return mp_obj_new_int(a - b);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(calculator_subtract_obj, calculator_subtract);

// Define module globals table
STATIC const mp_rom_map_elem_t calculator_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_calculator) },
    { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&calculator_add_obj) },
    { MP_ROM_QSTR(MP_QSTR_subtract), MP_ROM_PTR(&calculator_subtract_obj) },
};
STATIC MP_DEFINE_CONST_DICT(calculator_module_globals, calculator_module_globals_table);

// Define module object
const mp_obj_module_t calculator_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&calculator_module_globals,
};

// Register the module
MP_REGISTER_MODULE(MP_QSTR_calculator, calculator_module); 