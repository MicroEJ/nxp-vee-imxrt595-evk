/*
 * C
 *
 * Copyright 2024 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#include <stdlib.h>
#include <string.h>

#include "LLKERNEL_impl.h"

// Your implementation of malloc()
#define KERNEL_MALLOC(size) malloc((size_t)(size))

// Your implementation of free()
#define KERNEL_FREE(addr) free((void*)(addr))

// Your implementation of 'ASSERT(0)'
#define KERNEL_ASSERT_FAIL() while(1)

// Utility macros for allocating RAM and ROM areas with required alignment constraints
#define KERNEL_AREA_GET_MAX_SIZE(size, alignment) ((size)+((alignment)-1))
#define KERNEL_AREA_GET_START_ADDRESS(addr, alignment) ((void*)((((int32_t)(addr))+(alignment)-1)&~((alignment)-1)))

typedef struct installed_feature{
   void* ROM_area;
   void* RAM_area;
} installed_feature_t;

int32_t LLKERNEL_IMPL_allocateFeature(int32_t size_ROM, int32_t size_RAM) {
   int32_t ret = 0;
   int total_size = sizeof(installed_feature_t);
   total_size += KERNEL_AREA_GET_MAX_SIZE(size_ROM, LLKERNEL_ROM_AREA_ALIGNMENT);
   total_size += KERNEL_AREA_GET_MAX_SIZE(size_RAM, LLKERNEL_RAM_AREA_ALIGNMENT);

   void* total_area = KERNEL_MALLOC(total_size);
   if(NULL != total_area){
      installed_feature_t* f = (installed_feature_t*)total_area;
      f->ROM_area = KERNEL_AREA_GET_START_ADDRESS((void*)(((int32_t)f)+((int32_t)sizeof(installed_feature_t))), LLKERNEL_ROM_AREA_ALIGNMENT);
      f->RAM_area = KERNEL_AREA_GET_START_ADDRESS((void*)(((int32_t)f->ROM_area)+size_ROM), LLKERNEL_RAM_AREA_ALIGNMENT);
      ret = (int32_t)f;
   } // else out of memory

   return ret;
}

void LLKERNEL_IMPL_freeFeature(int32_t handle) {
   KERNEL_FREE(handle);
}

int32_t LLKERNEL_IMPL_getAllocatedFeaturesCount(void) {
   // No persistency support
   return 0;
}

int32_t LLKERNEL_IMPL_getFeatureHandle(int32_t allocation_index) {
   // No persistency support
   KERNEL_ASSERT_FAIL();
}

void* LLKERNEL_IMPL_getFeatureAddressRAM(int32_t handle) {
   return ((installed_feature_t*)handle)->RAM_area;
}

void* LLKERNEL_IMPL_getFeatureAddressROM(int32_t handle) {
   return ((installed_feature_t*)handle)->ROM_area;
}

int32_t LLKERNEL_IMPL_copyToROM(void* dest_address_ROM, void* src_address, int32_t size) {
   memcpy(dest_address_ROM, src_address, size);
   return LLKERNEL_OK;
}

int32_t LLKERNEL_IMPL_flushCopyToROM(void) {
   return LLKERNEL_OK;
}

int32_t LLKERNEL_IMPL_onFeatureInitializationError(int32_t handle, int32_t error_code) {
   // No persistency support
   KERNEL_ASSERT_FAIL();
   return 0;
}
