/*
 * C
 *
 * Copyright 2015-2020 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

#if !defined BUTTONS_MANAGER_H
#define BUTTONS_MANAGER_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include "buttons_helper_configuration.h"

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------

/*!
 * @brief Initializes the buttons_manager module
 */
void BUTTONS_MANAGER_initialize(void);

/*
 * @brief Enable the GPIO hardware interrupts
 */
void BUTTONS_MANAGER_enable_interrupts(void);

/*
 * @brief Disable the GPIO hardware interrupts
 */
void BUTTONS_MANAGER_disable_interrupts(void);

/*
 * @brief Buttons interrupt
 */
void BUTTONS_MANAGER_interrupt(void);

#endif // !defined BUTTONS_MANAGER_H

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

