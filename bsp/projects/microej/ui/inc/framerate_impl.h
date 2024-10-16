/*
 * C
 *
 * Copyright 2014-2020 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

/*
 * Implement the *_impl* functions according the CPU/OS/Compiler
 */

#if !defined FRAMERATE_IMPL_H
#define FRAMERATE_IMPL_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include "framerate.h"

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------

#if FRAMERATE_ENABLED == 1

/*
 * Framerate task have just to call this function
 */
void framerate_task_work(void);

/*
 * Create and start a framerate task
 */
int32_t framerate_impl_start_task(void);

/*
 * Sleep the framerate task
 *
 * @param[in] ms: Sleeping period in milliseconds
 */
void framerate_impl_sleep(uint32_t ms);

#endif	// FRAMERATE_ENABLED

#endif // !defined FRAMERATE_IMPL_H

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

