/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Your Name
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */

#include <stdio.h>
#include "py/runtime.h"
#include "py/obj.h"
#include "py/builtin.h"

// Define STATIC if not already defined
#ifndef STATIC
#define STATIC static
#endif

// External C function declaration from matter_main.c
extern esp_err_t matter_init(void);

// Matter start function
STATIC mp_obj_t matter_start(void) {
    esp_err_t err = matter_init();
    if (err != ESP_OK) {
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Failed to initialize Matter"));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(matter_start_obj, matter_start);

// Define module globals table
STATIC const mp_rom_map_elem_t matter_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_matter) },
    { MP_ROM_QSTR(MP_QSTR_start), MP_ROM_PTR(&matter_start_obj) },
};
STATIC MP_DEFINE_CONST_DICT(matter_module_globals, matter_module_globals_table);

// Define module object
const mp_obj_module_t matter_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&matter_module_globals,
};

// Register the module
MP_REGISTER_MODULE(MP_QSTR_matter, matter_module); 