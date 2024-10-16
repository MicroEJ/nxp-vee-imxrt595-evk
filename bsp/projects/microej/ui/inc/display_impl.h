/*
 * C
 *
 * Copyright 2022-2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/*
 * @file
 * @brief Implementation of MicroEJ MicroUI library low level API "LLUI_DISPLAY_impl.h"
 * for the NXP MIMXRT595-EVK board. Provides a set of functions to extend the implementation.
 * @author MicroEJ Developer Team
 * @version 7.0.0
 *
 * @brief This file lists a set of functions called by the display*.c files. First functions
 * are mandatory; optional functions are listed in a second time.
 *
 * These functions are
 * optional and a stub implementation is already available in the CCO (see display_stub.c).
 */

#if !defined DISPLAY_IMPL_H
#define DISPLAY_IMPL_H

#if defined __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>

#include "display_framebuffer.h"

// --------------------------------------------------------------------------------
// Optional functions to implement (already implemented as weak functions)
// --------------------------------------------------------------------------------

/*
 * @brief Notifies the LLUI_DISPLAY_IMPL is initialized. The implementation can
 * initialize 3rd-party elements.
 *
 * Default implementation does nothing.
 */
void DISPLAY_IMPL_initialized(void) ;

/*
 * @brief Notifies the first frame buffer will be used just after this call and
 * the second frame buffer will not be used anymore until the next call to
 * DISPLAY_IMPL_update_frame_buffer_status().
 *
 * Default implementation does nothing.
 *
 * @param[in] frame_buffer_on: the frame buffer that will be used
 * @param[in] frame_buffer_off: the frame buffer that not used anymore
 */
void DISPLAY_IMPL_update_frame_buffer_status(framebuffer_t* frame_buffer_on, framebuffer_t* frame_buffer_off);

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // !defined DISPLAY_IMPL_H
