# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.27.0)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT DEFINED SdkOverlayRootDirPath)
    SET(SdkOverlayRootDirPath ${ProjDirPath}/../../../sdk_overlay/)
endif()

if (NOT DEFINED VeeSdkRootDirPath)
    SET(VeeSdkRootDirPath ${ProjDirPath}/../../../mcux-sdk/core/)
endif()

if (NOT DEFINED RtosRootDirPath)
    SET(RtosRootDirPath ${ProjDirPath}/../../../mcux-sdk/rtos/)
endif()

if (NOT DEFINED MicroejDirPath)
    SET(MicroejDirPath ${ProjDirPath}/../../microej/)
endif()


find_package(Git)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

project(mimxrt595_freertos-bsp)

file (STRINGS "${ProjDirPath}/../../../nvee_version.txt" VEE_VERSION)

set(MCUX_DEVICE MIMXRT595S_cm33)
set(PROJECT_NAME mimxrt595_freertos-bsp)
set(MCUX_SDK_PROJECT_NAME ${PROJECT_NAME}.elf)
cmake_path(GET MCUX_SDK_PROJECT_NAME STEM MCUX_SDK_PROJECT_NAME_NO_EXT)

# config to select component, the format is CONFIG_USE_${component}
set(CONFIG_USE_component_serial_manager_uart true)
set(CONFIG_USE_driver_flexcomm_usart true)

include (${ProjDirPath}/flags.cmake)

execute_process(COMMAND
  "${GIT_EXECUTABLE}" describe --always --abbrev=8 --dirty
  WORKING_DIRECTORY "${ProjDirPath}"
  OUTPUT_VARIABLE GIT_SHA_1
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file("${ProjDirPath}/../main/src/tree_version.c.in" "${CMAKE_CURRENT_BINARY_DIR}/tree_version.c" @ONLY)

add_executable(${MCUX_SDK_PROJECT_NAME}
    "${ProjDirPath}/../board/src/board.c"
    "${ProjDirPath}/../board/src/clock_config.c"
    "${ProjDirPath}/../board/src/display_support.c"
    "${ProjDirPath}/../board/src/pin_mux.c"
    "${ProjDirPath}/../freertos/src/SEGGER_SYSVIEW_Config_FreeRTOS.c"
    "${ProjDirPath}/../simple_gfx_app/src/simple_gfx_app_imp.c"
    "${ProjDirPath}/../main/src/core_test_natives.c"
    "${ProjDirPath}/../main/src/cpuload.c"
    "${ProjDirPath}/../main/src/cpuload_impl_FreeRTOS.c"
    "${ProjDirPath}/../main/src/fault_handlers.c"
    "${ProjDirPath}/../main/src/interrupts.c"
    "${ProjDirPath}/../main/src/LLBSP.c"
    "${ProjDirPath}/../main/src/LLEXT_RES_impl.c"
    "${ProjDirPath}/../main/src/LLMJVM_FreeRTOS.c"
    "${ProjDirPath}/../main/src/main.c"
    "${ProjDirPath}/../main/src/microjvm_main.c"
    "${ProjDirPath}/../main/src/monitor.c"
    "${ProjDirPath}/../main/src/os_support.c"
    "${ProjDirPath}/../main/src/stack_overflow_impl_FreeRTOS.c"
    "${ProjDirPath}/../main/src/time_hardware_timer.c"
    "${ProjDirPath}/../main/src/trace_platform.c"
    "${MicroejDirPath}/osal/src/osal_FreeRTOS.c"
    "${MicroejDirPath}/lowpower/src/power_manager.c"
    "${MicroejDirPath}/lowpower/src/fsl_tickless_rtc.c"
    "${MicroejDirPath}/thirdparty/freetype/src/wrappers/ft_base_wrapper.c"
    "${MicroejDirPath}/thirdparty/freetype/src/wrappers/ft_otf_wrapper.c"
    "${MicroejDirPath}/thirdparty/freetype/src/wrappers/ft_ttf_wrapper.c"
    "${MicroejDirPath}/thirdparty/freetype/src/wrappers/ft_vector_wrapper.c"
    "${MicroejDirPath}/thirdparty/harfbuzz/src/hb-alloc.c"
    "${MicroejDirPath}/thirdparty/systemview/src/SEGGER_RTT.c"
    "${MicroejDirPath}/thirdparty/systemview/src/SEGGER_SYSVIEW.c"
    "${MicroejDirPath}/thirdparty/systemview-freertos/src/SEGGER_SYSVIEW_FreeRTOS.c"
    "${MicroejDirPath}/trace/src/LLMJVM_MONITOR_sysview.c"
    "${MicroejDirPath}/trace/src/LLTRACE_sysview.c"
    "${MicroejDirPath}/ui/src/buttons_helper.c"
    "${MicroejDirPath}/ui/src/buttons_manager.c"
    "${MicroejDirPath}/ui/src/display_dma.c"
    "${MicroejDirPath}/ui/src/display_framebuffer.c"
    "${MicroejDirPath}/ui/src/event_generator.c"
    "${MicroejDirPath}/ui/src/framerate.c"
    "${MicroejDirPath}/ui/src/framerate_impl_FreeRTOS.c"
    "${MicroejDirPath}/ui/src/LLDW_PAINTER_impl.c"
    "${MicroejDirPath}/ui/src/LLUI_DISPLAY_impl.c"
    "${MicroejDirPath}/ui/src/LLUI_INPUT_impl.c"
    "${MicroejDirPath}/ui/src/LLUI_PAINTER_impl.c"
    "${MicroejDirPath}/ui/src/touch_helper.c"
    "${MicroejDirPath}/ui/src/touch_manager.c"
    "${MicroejDirPath}/ui/src/ui_display_brs.c"
    "${MicroejDirPath}/ui/src/ui_display_brs_legacy.c"
    "${MicroejDirPath}/ui/src/ui_display_brs_predraw.c"
    "${MicroejDirPath}/ui/src/ui_display_brs_single.c"
    "${MicroejDirPath}/ui/src/ui_drawing.c"
    "${MicroejDirPath}/ui/src/ui_drawing_vglite.c"
    "${MicroejDirPath}/ui/src/ui_drawing_vglite_path.c"
    "${MicroejDirPath}/ui/src/ui_drawing_vglite_process.c"
    "${MicroejDirPath}/ui/src/ui_rect_util.c"
    "${MicroejDirPath}/ui/src/ui_vglite.c"
    "${MicroejDirPath}/util/src/mej_debug.c"
    "${MicroejDirPath}/util/src/mej_math.c"
    "${MicroejDirPath}/util/src/pool.c"
    "${MicroejDirPath}/vg/src/LLVG_PAINTER_impl.c"
    "${MicroejDirPath}/vg/src/vg_drawing_bvi.c"
    "${MicroejDirPath}/vg/src/vg_drawing_stub.c"
    "${MicroejDirPath}/vg/src/vg_drawing_vglite.c"
    "${MicroejDirPath}/vg/src/vg_drawing.c"
    "${MicroejDirPath}/vg/src/LLVG_BVI_stub.c"
    "${MicroejDirPath}/vg/src/LLVG_FONT_freetype.c"
    "${MicroejDirPath}/vg/src/LLVG_FONT_PAINTER_freetype_vglite.c"
    "${MicroejDirPath}/vg/src/LLVG_FONT_stub.c"
    "${MicroejDirPath}/vg/src/LLVG_GRADIENT_impl.c"
    "${MicroejDirPath}/vg/src/LLVG_impl.c"
    "${MicroejDirPath}/vg/src/LLVG_MATRIX_impl.c"
    "${MicroejDirPath}/vg/src/LLVG_PATH_impl.c"
    "${MicroejDirPath}/vg/src/LLVG_PATH_stub.c"
    "${MicroejDirPath}/vg/src/LLVG_RAW_impl.c"
    "${MicroejDirPath}/vg/src/LLVG_vglite.c"
    "${MicroejDirPath}/vg/src/microvg_helper.c"
    "${MicroejDirPath}/vglite_support/vglite_support.c"
    "${MicroejDirPath}/vglite_window/vglite_window.c"
    "${MicroejDirPath}/stub/src/stub.c"
    "${VeeSdkRootDirPath}/devices/MIMXRT595S/mcuxpresso/startup_mimxrt595s_cm33.c"
    ${CMAKE_CURRENT_BINARY_DIR}/tree_version.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME}  PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../board/inc
    ${ProjDirPath}/../freertos/inc
    ${ProjDirPath}/../main/inc
    ${MicroejDirPath}/lowpower/inc
    ${MicroejDirPath}/trace/inc
    ${MicroejDirPath}/ui/inc
    ${MicroejDirPath}/util/inc
    ${MicroejDirPath}/vg/inc
    ${MicroejDirPath}/thirdparty/systemview/inc
    ${MicroejDirPath}/thirdparty/systemview-freertos/inc
    ${MicroejDirPath}/thirdparty/freetype/inc
    ${MicroejDirPath}/thirdparty/harfbuzz/inc
    ${MicroejDirPath}/osal/inc
    ${MicroejDirPath}/platform/inc
    ${MicroejDirPath}/vglite_support
    ${MicroejDirPath}/vglite_window
)

add_definitions(
    -D__USE_CMSIS
    -DDEBUG
    -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1
    -DBOOT_HEADER_ENABLE=1
    -DCPU_MIMXRT595SFFOB_cm33
    -DBOARD_ENABLE_PSRAM_CACHE=0
    -DFLEXIO_MCULCD_DATA_BUS_WIDTH=8
    -DDBI_FLEXIO_USE_SMARTDMA=1
    -DCUSTOM_VGLITE_MEMORY_CONFIG=1
    -DVG_RESOLVE_ENGINE=0
    -DVG_PE_COLOR_KEY=0
    -DVG_IM_INDEX_FORMAT=0
    -DVG_AYUV_INPUT_OUTPUT=0
    -DVG_DOUBLE_IMAGE=0
    -DVG_RECTANGLE_STRIP_MODE=0
    -DVG_MMU=0
    -DVG_DRIVER_SINGLE_THREAD=1
    -DVG_IM_FILTER=0
    -DVG_IM_YUV_PACKET=1
    -DVG_IM_YUV_PLANAR=0
    -DVG_PE_YUV_PACKET=1
    -DVG_TARGET_TILED=1
    -DVG_COMMAND_CALL=1
    -DVG_SHARE_BUFFER_IM_16K=0
    -DVG_OFFLINE_MODE=0
    -DVG_RESOLUTION_2880=0
    -DVG_PE_PREMULTIPLY=0
    -DVG_POST_CONVERTER=0
    -DVG_PRE_CONVERTER=0
    -DVG_RENDER_BY_MESH=0
    -DVG_TARGET_FAST_CLEAR=0
    -DVG_BUFFER_NUMBER_OF_TARGET=0
    -DVG_VIDEO_CLEAR_CONTROL=0
    -DVG_VIDEO_CONTROL=0
    -DVGLITE_TST_FIRMWARE=0
    -DVG_LITE_SYS_GPU_CTRL=0
    -DSERIAL_PORT_TYPE_UART=1
    -DFSL_RTOS_FREE_RTOS
    -DPRINTF_FLOAT_ENABLE=1
    -DPRINTF_ADVANCED_ENABLE=1
    -DENABLE_SYSTEM_VIEW=1
    -DSDK_I2C_BASED_COMPONENT_USED=1
    -D_VG_LITE_IRQ_CALLBACK=1
    -DSL_WFX_PROD_KEY=1
    -DLWIP_2_1_2
    -DSDK_DEBUGCONSOLE_UART
    -DFT_CONFIG_MODULES_H=\"freetype/config/ftmodule.h\"
    -DFT2_BUILD_LIBRARY
    -DRTT_USE_ASM=0
)

SET(CMAKE_MODULE_PATH
    ${MicroejDirPath}/gpio
    ${VeeSdkRootDirPath}/boards/evkmimxrt595/flash_config/
    ${VeeSdkRootDirPath}/components/ft3267
    ${VeeSdkRootDirPath}/components/serial_manager
    ${VeeSdkRootDirPath}/components/pca9420
    ${VeeSdkRootDirPath}/components/lists
    ${VeeSdkRootDirPath}/components/uart
    ${VeeSdkRootDirPath}/components/video
    ${VeeSdkRootDirPath}/components/video/display
    ${VeeSdkRootDirPath}/components/video/display/dbi
    ${VeeSdkRootDirPath}/components/video/display/dbi/flexio
    ${VeeSdkRootDirPath}/components/video/display/dc
    ${VeeSdkRootDirPath}/components/video/display/dc/ssd1963
    ${VeeSdkRootDirPath}/components/video/display/dc/lcdif
    ${VeeSdkRootDirPath}/components/video/display/dc/dsi_cmd
    ${VeeSdkRootDirPath}/components/video/display/fbdev
    ${VeeSdkRootDirPath}/components/video/display/mipi_dsi_cmd
    ${VeeSdkRootDirPath}/components/video/display/rm67162
    ${VeeSdkRootDirPath}/components/video/display/rm68191
    ${VeeSdkRootDirPath}/components/video/display/rm68200
    ${VeeSdkRootDirPath}/CMSIS/Core/Include
    ${VeeSdkRootDirPath}/CMSIS/DSP
    ${VeeSdkRootDirPath}/devices/MIMXRT595S
    ${VeeSdkRootDirPath}/devices/MIMXRT595S/drivers/
    ${VeeSdkRootDirPath}/devices/MIMXRT595S/utilities/
    ${VeeSdkRootDirPath}/devices/MIMXRT595S/utilities/debug_console/
    ${VeeSdkRootDirPath}/drivers/common/
    ${VeeSdkRootDirPath}/drivers/flexcomm/
    ${VeeSdkRootDirPath}/drivers/mipi_dsi/
    ${VeeSdkRootDirPath}/drivers/lpc_dma/
    ${VeeSdkRootDirPath}/drivers/flexio/
    ${VeeSdkRootDirPath}/drivers/flexspi/
    ${VeeSdkRootDirPath}/drivers/inputmux/
    ${VeeSdkRootDirPath}/drivers/lpc_gpio/
    ${VeeSdkRootDirPath}/drivers/powerquad/
    ${VeeSdkRootDirPath}/drivers/lpc_rtc/
    ${VeeSdkRootDirPath}/drivers/smartdma/
    ${VeeSdkRootDirPath}/drivers/trng/
    ${VeeSdkRootDirPath}/drivers/
    ${VeeSdkRootDirPath}/utilities/debug_console/
    ${VeeSdkRootDirPath}/utilities/misc_utilities/
    ${VeeSdkRootDirPath}/utilities/assert/
    ${VeeSdkRootDirPath}/utilities/
    ${VeeSdkRootDirPath}/drivers/cache/cache64/
    ${VeeSdkRootDirPath}/drivers/ctimer/
    ${VeeSdkRootDirPath}/drivers/lpc_iopctl/
    ${VeeSdkRootDirPath}/drivers/pint/
    ${SdkOverlayRootDirPath}/rtos/freertos/freertos-kernel/
    ${SdkOverlayRootDirPath}/middleware/vglite/
    ${MicroejDirPath}/thirdparty/freetype/
    ${MicroejDirPath}/thirdparty/harfbuzz/
)

# include modules
include(driver_pca9420)
include(component_usart_adapter)
include(component_lists)
include(component_serial_manager)
include(component_serial_manager_uart)
include(device_CMSIS)
include(driver_cache_cache64)
include(driver_clock)
include(driver_common)
include(driver_ctimer)
include(driver_dbi_flexio_smartdma)
include(driver_dc-fb-dsi-cmd)
include(driver_display-rm67162)
include(driver_display-rm68191)
include(driver_display-rm68200)
include(driver_fbdev)
include(driver_flash_config_evkmimxrt595)
include(driver_flexcomm_i2c)
include(driver_flexcomm)
include(driver_flexcomm_usart_dma)
include(driver_flexcomm_usart)
include(driver_flexio)
include(driver_flexio_spi)
include(driver_flexspi)
include(driver_ft3267)
include(driver_iap)
include(driver_inputmux)
include(driver_lpc_dma)
include(driver_lpc_gpio)
include(driver_lpc_rtc)
include(driver_lpc_smartdma)
include(driver_mipi_dsi)
include(driver_mipi_dsi_smartdma)
include(driver_power)
include(driver_powerquad_cmsis)
include(driver_powerquad)
include(driver_reset)
include(driver_trng)
include(driver_video-common)
include(middleware_freertos-kernel_cm33_nonsecure_port)
include(middleware_freertos-kernel_heap_4)
include(middleware_freertos-kernel_MIMXRT595S_cm33)
include(middleware_vglite)
include(nxp_gpio)
include(utilities_misc_utilities_MIMXRT595S_cm33)
include(utility_assert)
include(utility_debug_console)
include(driver_lpc_iopctl)
include(driver_pint)
include(thirdparty_freetype)
include(thirdparty_harfbuzz)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE 
    ${MicroejDirPath}/platform/lib/microejapp.o
    ${MicroejDirPath}/platform/lib/microejruntime.a
)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ./${MCUX_SDK_PROJECT_NAME} ./${MCUX_SDK_PROJECT_NAME_NO_EXT}.bin)
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Oihex ./${MCUX_SDK_PROJECT_NAME} ./${MCUX_SDK_PROJECT_NAME_NO_EXT}.hex)

SET_TARGET_PROPERTIES(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ./${MCUX_SDK_PROJECT_NAME_NO_EXT}.bin)
SET_TARGET_PROPERTIES(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ./${MCUX_SDK_PROJECT_NAME_NO_EXT}.hex)
