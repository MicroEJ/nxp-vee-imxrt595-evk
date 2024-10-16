/*
 * C
 *
 * Copyright 2019-2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/*
 * @file
 * @brief Implementation of MicroEJ MicroUI library low level API "LLUI_DISPLAY_impl.h"
 * for the NXP MIMXRT595-EVK board. Provides a set of defines to configure the implementation.
 * @author MicroEJ Developer Team
 */

#if !defined DISPLAY_CONFIGURATION_H
# define DISPLAY_CONFIGURATION_H

#if defined __cplusplus
extern "C" {
#endif

//#error "This header must be customized with platform specific configuration. Remove this #error when done. This file is not modified when a new version of the CCO is installed."

/**
 * @brief Compatibility sanity check value.
 * This define value is checked in the implementation to validate that the version of this configuration
 * is compatible with the implementation.
 *
 * This value must not be changed by the user of the CCO.
 * This value must be incremented by the implementor of the CCO when a configuration define is added, deleted or modified.
 */
#define DISPLAY_CONFIGURATION_VERSION (3)

// -----------------------------------------------------------------------------
// Macros and Defines
// -----------------------------------------------------------------------------

/*
 * @brief Width of the display panel
 */
#define DISPLAY_PANEL_WIDTH (400)

/*
 * @brief Height of the display panel
 */
#define DISPLAY_PANEL_HEIGHT (392)

/*
 * @brief Width of the frame buffers
 */
#define FRAME_BUFFER_WIDTH (392)

/*
 * @brief Height of the frame buffers
 */
#define FRAME_BUFFER_HEIGHT (392)

/*
 * @brief Source image line alignment (in bytes), required by VGLite library
 * when an image is used as source: 32 bits for RGB565 format
 * (see _check_source_aligned() in vg_lite.c).
 */
#define VGLITE_IMAGE_LINE_ALIGN_BYTE (32)

/*
 * @brief Frame buffer line alignment (in bytes), required by VGLite library
 * when frame buffer is used as source.
 * Note: Set (1) to not use the frame buffer as source image.
 * Note 2: Require a patch in fsl_dc_fb_dsi_cmd.c
 */
#define FRAME_BUFFER_LINE_ALIGN_BYTE (1) /* 1 | VGLITE_IMAGE_LINE_ALIGN_BYTE */

/*
 * @brief Available number of frame buffers
 */
#define FRAME_BUFFER_COUNT (2)

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // !defined DISPLAY_CONFIGURATION_H
