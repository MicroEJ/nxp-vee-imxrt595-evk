/*
 * C
 *
 * Copyright 2020-2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/*
 * @file
 * @brief Implementation of MicroEJ MicroUI library low level API "LLUI_DISPLAY_impl.h"
 * for the NXP MIMXRT595-EVK board. Provides a set of functions to drive a DMA (to use
 * it as "framebuffer backcopy").
 * @author MicroEJ Developer Team
 * @version 7.0.0
 */

#if !defined DISPLAY_DMA_H
#define DISPLAY_DMA_H

#if defined __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include "display_framebuffer.h"
#include "ui_display_brs.h"

// -----------------------------------------------------------------------------
// Macros and Defines
// -----------------------------------------------------------------------------

#if UI_DISPLAY_BRS == UI_DISPLAY_BRS_LEGACY
#define DISPLAY_DMA_ENABLED       ( FRAME_BUFFER_COUNT > 1 )
#endif

// --------------------------------------------------------------------------------
// Optional functions to implement (already implemented as weak functions)
// --------------------------------------------------------------------------------

/*
 * @brief Notifies the DMA will be used just after this call. The implementation
 * must ensure the DMA can be used (power management, clocks, etc.).
 *
 * Default implementation does nothing.
 */
void DISPLAY_DMA_IMPL_notify_dma_start(void) ;

/*
 * @brief Notifies the DMA is not used anymore by the library until the next call to
 * DISPLAY_DMA_IMPL_notify_dma_start().
 *
 * Default implementation does nothing.
 */
void DISPLAY_DMA_IMPL_notify_dma_stop(void) ;

// -----------------------------------------------------------------------------
// API
// -----------------------------------------------------------------------------

/*
 * @brief: Initialize the DMA synchronization between the framebuffers
 *
 * @param[in] framebuffers: display framebuffers
 */
void DISPLAY_DMA_initialize(const framebuffer_t * framebuffers[]);

/*
 * @brief: Starts a DMA transfert
 *
 * @param[in] src: source framebuffer
 * @param[in] dst: destination framebuffer
 * @param[in] ymin: first line to transfert
 * @param[in] ymax: last line to transfert + 1
 */
void DISPLAY_DMA_start(framebuffer_t *src, framebuffer_t *dst, int ymin, int ymax);

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // !defined DISPLAY_DMA_H
