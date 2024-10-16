/*
 * C
 *
 * Copyright 2019-2020 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

#if !defined BUTTONS_HELPER_CONFIGURATION_H
#define BUTTONS_HELPER_CONFIGURATION_H

// -----------------------------------------------------------------------------
// Macros and Defines
// -----------------------------------------------------------------------------

// Number of buttons the helper has to manage
#define BUTTONS_HELPER_NUMBER_OF_BUTTONS	2

#define BUTTONS_HELPER_VM_DUMP_ON_BUTTON	1

// -----------------------------------------------------------------------------
// Types
// -----------------------------------------------------------------------------

typedef enum
{
	BUTTON_SW1 = 0,
	BUTTON_SW2,
} button_id_t;

#endif // !defined BUTTONS_HELPER_CONFIGURATION_H

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

