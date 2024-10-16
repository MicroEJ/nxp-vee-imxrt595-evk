/*
 * Copyright 2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#include <stdio.h>

#include "ui_drawing_vglite.h"
#include "vg_drawing_vglite.h"

/*
 * The current VEE port supports two output formats: BufferedVectorImage (see the MicroVG CCO) and ARGB8888 (this file).
 * To add another output format, add the same mechanism as in the UI testsuite VEE port (see ui_drawing_composite.c) and modify this file accordingly.
 */

#define UI_DRAWING_IDENTIFIER_ARGB8888_FORMAT 2 // fake identifier to not overlap ui_drawing_composite
#define VG_DRAWING_IDENTIFIER_ARGB8888_FORMAT UI_DRAWING_IDENTIFIER_ARGB8888_FORMAT

#define UI_DRAWING_ARGB8888_is_drawer CONCAT(UI_DRAWING_is_drawer_, UI_DRAWING_IDENTIFIER_ARGB8888_FORMAT)
#define UI_DRAWING_ARGB8888_getNewImageStrideInBytes CONCAT(UI_DRAWING_getNewImageStrideInBytes_, UI_DRAWING_IDENTIFIER_ARGB8888_FORMAT)
#define VG_DRAWING_ARGB8888_drawPath CONCAT(VG_DRAWING_drawPath_, VG_DRAWING_IDENTIFIER_ARGB8888_FORMAT)


bool UI_DRAWING_ARGB8888_is_drawer(jbyte image_format) {
	return image_format == MICROUI_IMAGE_FORMAT_ARGB8888;
}

uint32_t UI_DRAWING_ARGB8888_getNewImageStrideInBytes(jbyte image_format, uint32_t image_width, uint32_t image_height, uint32_t default_stride) {
	return UI_DRAWING_getNewImageStrideInBytes(image_format, image_width, image_height, default_stride);
}

DRAWING_Status VG_DRAWING_ARGB8888_drawPath(MICROUI_GraphicsContext* gc, jbyte* path, jint x, jint y, jfloat* matrix, jint fillRule, jint blend, jint color) {
	return VG_DRAWING_drawPath_0(gc, path, x, y, matrix, fillRule, blend, color);
}
