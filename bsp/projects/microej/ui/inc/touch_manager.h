/*
 * C
 *
 * Copyright 2015-2020 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

#if !defined TOUCH_MANAGER_H
#define TOUCH_MANAGER_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include <stdint.h>

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------

/*
 * @brief Initializes the touch manager module
 */
void TOUCH_MANAGER_initialize(void);

/*
 * @brief Touch interrupt
 */
void TOUCH_MANAGER_interrupt(void);

#endif // !defined TOUCH_MANAGER_H

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

