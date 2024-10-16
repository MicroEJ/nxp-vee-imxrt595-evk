/*
 * C
 *
 * Copyright 2020-2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/*
 * @file
 * @brief Implementation of MicroEJ MicroUI library low level API "LLUI_DISPLAY_impl.h"
 * for the NXP MIMXRT595-EVK board.
 * @author MicroEJ Developer Team
 * @version 7.0.0
 */

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include "display_framebuffer.h"

#include "fsl_dc_fb.h"

// -----------------------------------------------------------------------------
// Global Variables
// -----------------------------------------------------------------------------

_Pragma( "location = \"framebuffer0\"") static framebuffer_t s_frameBuffer0;
#define FRAME_BUFFER0_ADDR &s_frameBuffer0

#if defined (FRAME_BUFFER_COUNT) && (FRAME_BUFFER_COUNT > 1)
_Pragma( "location = \"framebuffer1\"") static framebuffer_t s_frameBuffer1;
#define FRAME_BUFFER1_ADDR &s_frameBuffer1
#endif

#if defined (FRAME_BUFFER_COUNT) && (FRAME_BUFFER_COUNT > 2)
_Pragma( "location = \"framebuffer2\"") static framebuffer_t s_frameBuffer2;
#define FRAME_BUFFER2_ADDR &s_frameBuffer2
#endif

// cppcheck-suppress [misra-c2012-9.3] array is fully initialized
const framebuffer_t * s_frameBufferAddress[FRAME_BUFFER_COUNT] = {
		FRAME_BUFFER0_ADDR,
#if defined (FRAME_BUFFER_COUNT) && (FRAME_BUFFER_COUNT > 1)
		FRAME_BUFFER1_ADDR,
#endif
#if defined (FRAME_BUFFER_COUNT) && (FRAME_BUFFER_COUNT > 2)
		FRAME_BUFFER2_ADDR
#endif
	};

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------
