/*
 * C
 *
 * Copyright 2020 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include "mej_debug.h"

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------

uint32_t __mej_debug_lvls = 0;

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------

/*
 * Enable a debug level
 * @param level: level to enable
 */
void MEJ_DEBUG_enable(int level) {
    __mej_debug_lvls |= level;
}

void MEJ_DEBUG_disable(int level) {
    __mej_debug_lvls &= ~(level);
}