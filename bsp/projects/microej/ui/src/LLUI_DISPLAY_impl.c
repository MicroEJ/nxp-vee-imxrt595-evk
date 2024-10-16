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

#include <stdarg.h>

#include <LLUI_DISPLAY_impl.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include "bsp_util.h"
#include "display_dma.h"
#include "ui_vglite.h"
#include "display_impl.h"
#include "framerate.h"
#include "ui_display_brs.h"
#include "power_manager.h"

#include "vglite_window.h"

#include "fsl_debug_console.h"
#include "fsl_dc_fb_dsi_cmd.h"

// -----------------------------------------------------------------------------
// Macros and Defines
// -----------------------------------------------------------------------------

#if (CUSTOM_VGLITE_MEMORY_CONFIG != 1)
#error "Application must be compiled with CUSTOM_VGLITE_MEMORY_CONFIG=1"
#else
#define VGLITE_COMMAND_BUFFER_SZ (128 * 1024)
#define VGLITE_HEAP_SZ 0x100000
#endif

#define DISPLAY_STACK_SIZE       (8 * 1024)
#define DISPLAY_TASK_PRIORITY    (12)                       /** Should be > tskIDLE_PRIORITY & < configTIMER_TASK_PRIORITY */
#define DISPLAY_TASK_STACK_SIZE  (DISPLAY_STACK_SIZE / 4)

// -----------------------------------------------------------------------------
// Global Variables
// -----------------------------------------------------------------------------

/* Allocate the heap and set the command buffer(s) size */
AT_NONCACHEABLE_SECTION_ALIGN(uint8_t vglite_heap[VGLITE_HEAP_SZ], 64);

void *vglite_heap_base        = &vglite_heap;
uint32_t vglite_heap_size     = VGLITE_HEAP_SZ;
uint32_t vglite_cmd_buff_size = VGLITE_COMMAND_BUFFER_SZ;

/*
 * @brief: Semaphore to synchronize the display flush with MicroUI
 */
static SemaphoreHandle_t sync_flush;
static uint8_t* dirty_area_addr;	// Address of the source framebuffer
static uint8_t dirty_area_flush;	// Identifier of the flush

#if UI_DISPLAY_BRS == UI_DISPLAY_BRS_LEGACY
static int32_t dirty_area_ymin;	// Top-most coordinate of the area to synchronize
static int32_t dirty_area_ymax;	// Bottom-most coordinate of the area to synchronize
#endif

/*
 * @brief VGLite display context
 */
static vg_lite_display_t display;

/*
 * @brief VGLite window context
 */
static vg_lite_window_t window;

// -----------------------------------------------------------------------------
// Private functions
// -----------------------------------------------------------------------------

/*
 * @brief: Task to manage display flushes and synchronize with hardware rendering
 * operations
 */
static void __display_task(void * pvParameters) {
		(void)pvParameters;

	do {

		xSemaphoreTake(sync_flush, portMAX_DELAY);

		// save the flush conf: can be modified by the next call to flush() as soon as LLUI_DISPLAY_setDrawingBuffer() will wake up the Graphics Engine
		uint8_t* flush_addr = dirty_area_addr;
#if UI_DISPLAY_BRS == UI_DISPLAY_BRS_PREDRAW                
		uint8_t flush_identifier = dirty_area_flush;
#endif

		// Two actions:
		// 1- wait for the end of previous swap (if not already done): wait the
		// end of sending of current frame buffer to display
		// 2- start sending of current_buffer to display (without waiting the
		// end)
		VGLITE_SwapBuffers(&window);

		// Increment framerate
		framerate_increment();

#if defined (FRAME_BUFFER_COUNT) && (FRAME_BUFFER_COUNT > 1)
		vg_lite_buffer_t *current_buffer = VGLITE_GetRenderTarget(&window);

		// Configure frame buffer powering; at that point current_buffer is back buffer
		// cppcheck-suppress [misra-c2012-11.3] cast to (framebuffer_t *) is valid
		DISPLAY_IMPL_update_frame_buffer_status(current_buffer->memory, (framebuffer_t *)flush_addr);

#if UI_DISPLAY_BRS == UI_DISPLAY_BRS_LEGACY
#if defined (DISPLAY_DMA_ENABLED) && (DISPLAY_DMA_ENABLED != 0)
		DISPLAY_DMA_start(
				(void *) flush_addr,
				current_buffer->memory,
				dirty_area_ymin,
				dirty_area_ymax);
		// back buffer currently in restoration; wait for restoration before unlocking next drawing
#else
		memcpy(
				&((uint8_t*) current_buffer->memory)[dirty_area_ymin * current_buffer->stride],
				&((uint8_t*) flush_addr)[dirty_area_ymin * current_buffer->stride],
				(dirty_area_ymax - dirty_area_ymin + 1) * current_buffer->stride
		);
		// back buffer restored can be used for next drawing
		if (!LLUI_DISPLAY_setDrawingBuffer(flush_identifier, current_buffer->memory, false)) {
			// end of flush not expected; the Graphics Engine keeps using previous back buffer;
			// have to cancel the buffers swap
			VGLITE_CancelSwapBuffers();
		}
#endif // defined DISPLAY_DMA_ENABLED
#elif UI_DISPLAY_BRS == UI_DISPLAY_BRS_PREDRAW

		// back buffer not restored but can be used for next drawing
		if (LLUI_DISPLAY_setDrawingBuffer(flush_identifier, current_buffer->memory, false)) {

			// wait for LCD refresh
			(void)FBDEV_GetFrameBuffer(&(display.g_fbdev), 0);

			// here: back buffer sent to the LCD, the buffer can be used again for next drawing
			// in case of no new drawing has been already performed in new back buffer

			// if another flush is already pending: xxx

			// reuse same back buffer if no drawing has been already performed
			if (LLUI_DISPLAY_setDrawingBuffer(flush_identifier, flush_addr, false)){
				// new back buffer set: cancel the previous swap to synchronoze the driver with the Graphics Engine
				// PRINTF("reuse 0x%x\n", flush_addr);
				VGLITE_CancelSwapBuffers();
			}
			// else: too late to set this old LCD buffer back buffer; nothing to do
		}
		else {
			// end of flush not expected; the Graphics Engine keeps using previous back buffer;
			// have to cancel the buffers swap
			VGLITE_CancelSwapBuffers();
		}


#endif // UI_DISPLAY_BRS
#else // FRAME_BUFFER_COUNT
		// buffer being sent, should not be used for next drawing until end of drawing
		(void)FBDEV_GetFrameBuffer(&(display.g_fbdev), 0);
#endif // FRAME_BUFFER_COUNT



	} while (1);
}

// -----------------------------------------------------------------------------
// Low Level API [optional]: weak functions
// -----------------------------------------------------------------------------

// See the header file for the function documentation
BSP_DECLARE_WEAK_FCNT void DISPLAY_IMPL_initialized(void) {
	// does nothing by default
}

// See the header file for the function documentation
BSP_DECLARE_WEAK_FCNT void DISPLAY_IMPL_update_frame_buffer_status(framebuffer_t* frame_buffer_on, framebuffer_t* frame_buffer_off) {
	// does nothing by default
	(void)frame_buffer_on;
	(void)frame_buffer_off;
}

/*
 * @brief Asks to the CCO MicroUI-VGLite to initialize the VG-Lite library. When this CCO
 * is not installed / available, the default function is used and does nothing.
 */
BSP_DECLARE_WEAK_FCNT void UI_VGLITE_init(void* sem) {
	// does nothing by default
	vSemaphoreDelete((SemaphoreHandle_t) sem);
}

// -----------------------------------------------------------------------------
// LLUI_DISPLAY_impl.h functions
// -----------------------------------------------------------------------------

// See the header file for the function documentation
void DISPLAY_DMA_IMPL_notify_dma_stop(void) {
#if UI_DISPLAY_BRS == UI_DISPLAY_BRS_PREDRAW
	LLUI_DISPLAY_notifyAsynchronousDrawingEnd(true);
#else
	// restoration done -> use the previous LCD buffer (== VGLITE_GetRenderTarget()) as new back buffer
	vg_lite_buffer_t *current_buffer = VGLITE_GetRenderTarget(&window);
	if (!LLUI_DISPLAY_setDrawingBuffer(dirty_area_flush, current_buffer->memory, true)) {
		// end of flush not expected; the Graphics Engine keeps using previous back buffer;
		// have to cancel the buffers swap
		VGLITE_CancelSwapBuffers();
	}
#endif
}

// See the header file for the function documentation
void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data) {

	/***************
	 * Init VGLite *
	 ***************/

	if (kStatus_Success != BOARD_PrepareVGLiteController()) {
		UI_VGLITE_IMPL_error(true, "Prepare VGlite controlor error");
	}

	vg_lite_error_t ret = VG_LITE_SUCCESS;

	if (VG_LITE_SUCCESS != VGLITE_CreateDisplay(&display)) {
		UI_VGLITE_IMPL_error(true, "VGLITE_CreateDisplay failed: VGLITE_CreateDisplay() returned error %d", ret);
	}

	// Initialize the window.
	if (VG_LITE_SUCCESS != VGLITE_CreateWindow(&display, &window)) {
		UI_VGLITE_IMPL_error(true, "VGLITE_CreateWindow failed: VGLITE_CreateWindow() returned error %d", ret);
	}
	
	// force to empty the counter
	for (uint8_t i = 0; i < window.bufferCount; i++) {
		(void)FBDEV_GetFrameBuffer(&(display.g_fbdev), 0);
	}

	UI_VGLITE_init((void*)xSemaphoreCreateBinary());

	/************
	 * Init DMA *
	 ************/

#if defined (DISPLAY_DMA_ENABLED) && (DISPLAY_DMA_ENABLED != 0)
	DISPLAY_DMA_initialize(s_frameBufferAddress);
#endif // defined DISPLAY_DMA_ENABLED

	/*************
	 * Init task *
	 *************/

	sync_flush = xSemaphoreCreateBinary();
	if (pdPASS != xTaskCreate(
			__display_task,
			"Display",
			DISPLAY_TASK_STACK_SIZE,
			NULL,
			DISPLAY_TASK_PRIORITY,
			NULL)){
		UI_VGLITE_IMPL_error(true, "failed to create task __display\n");
	}

	/****************
	 * Init MicroUI *
	 ****************/

	vg_lite_buffer_t *buffer = VGLITE_GetRenderTarget(&window);
	init_data->binary_semaphore_0 = (void*)xSemaphoreCreateBinary();
	init_data->binary_semaphore_1 = (void*)xSemaphoreCreateBinary();
	init_data->lcd_width = window.width;
	init_data->lcd_height = window.height;
	init_data->memory_width = FRAME_BUFFER_STRIDE_PIXELS;
	init_data->back_buffer_address = (uint8_t*)buffer->memory;

	// notify that the display is initialized
	DISPLAY_IMPL_initialized();
}

// See the header file for the function documentation
void LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t flush_identifier, const ui_rect_t areas[], size_t length) {

	uint8_t* addr = LLUI_DISPLAY_getBufferAddress(&gc->image);

	// store dirty area to restore after the flush
	dirty_area_addr = addr;
	dirty_area_flush = flush_identifier;

#if UI_DISPLAY_BRS == UI_DISPLAY_BRS_LEGACY
	dirty_area_ymin = areas[0].y1;
	dirty_area_ymax = areas[0].y2;
#endif

	// wakeup display task
	xSemaphoreGive(sync_flush);
}

// See the header file for the function documentation
void LLUI_DISPLAY_IMPL_binarySemaphoreTake(void* sem) {
	xSemaphoreTake((SemaphoreHandle_t)sem, portMAX_DELAY);
}

// See the header file for the function documentation
void LLUI_DISPLAY_IMPL_binarySemaphoreGive(void* sem, bool under_isr) {

	if (under_isr) {
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR((SemaphoreHandle_t)sem, &xHigherPriorityTaskWoken);
		if(xHigherPriorityTaskWoken != pdFALSE ) {
			// Force a context switch here.
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
	else  {
		xSemaphoreGive((SemaphoreHandle_t)sem);
	}
}

// See the header file for the function documentation
void UI_VGLITE_IMPL_notify_gpu_start(void) {
   power_manager_enable_low_power(POWER_GPU, LOW_POWER_FORBIDDEN);
}

// See the header file for the function documentation
void UI_VGLITE_IMPL_notify_gpu_stop(void) {
   power_manager_enable_low_power(POWER_GPU, LOW_POWER_AUTHORIZED);
}

// See the header file for the function documentation
void UI_VGLITE_IMPL_error(bool critical, const char* format, ...) {
	(void)format;
	va_list arg;
	va_start (arg, format);
	PRINTF(format, arg);
	va_end (arg);
	while (critical){}
}

// -----------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------
