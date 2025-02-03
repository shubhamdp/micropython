/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Damien P. George
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
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// qstrs specific to this port, only needed if they aren't auto-generated
// *FORMAT-OFF*

// Entries for sys.path
Q(/lib)

// Matter module
Q(matter)
Q(start)

// Matter Event Types
Q(EVENT_TYPES)
Q(COMMISSIONING_SESSION_STARTED)
Q(COMMISSIONING_SESSION_STOPPED)
Q(COMMISSIONING_WINDOW_OPENED)
Q(COMMISSIONING_WINDOW_CLOSED)
Q(FABRIC_WILL_BE_REMOVED)
Q(FABRIC_REMOVED)
Q(FABRIC_COMMITTED)
Q(FABRIC_UPDATED)

// Matter Endpoint Flags
Q(ENDPOINT_FLAGS)
Q(FLAG_NONE)
Q(FLAG_DESTROYABLE)
Q(FLAG_BRIDGE)

// Matter Cluster Flags
Q(CLUSTER_FLAGS)
Q(FLAG_INIT_FUNCTION)
Q(FLAG_ATTRIBUTE_CHANGED_FUNCTION)
Q(FLAG_SHUTDOWN_FUNCTION)
Q(FLAG_PRE_ATTRIBUTE_CHANGED_FUNCTION)
Q(FLAG_SERVER)
Q(FLAG_CLIENT)

// Matter Attribute Flags
Q(ATTRIBUTE_FLAGS)
Q(FLAG_WRITABLE)
Q(FLAG_NONVOLATILE)
Q(FLAG_MIN_MAX)
Q(FLAG_MUST_USE_TIMED_WRITE)
Q(FLAG_EXTERNAL_STORAGE)
Q(FLAG_SINGLETON)
Q(FLAG_NULLABLE)
Q(FLAG_OVERRIDE)
Q(FLAG_DEFERRED)
Q(FLAG_MANAGED_INTERNALLY)

// Matter Command Flags
Q(COMMAND_FLAGS)
Q(FLAG_CUSTOM)
Q(FLAG_ACCEPTED)
Q(FLAG_GENERATED)
