IF(NOT DEFINED FPU)
    SET(FPU "-mfloat-abi=hard -mfpu=fpv5-sp-d16")
ENDIF()

SET(ASM_COMMON_FLAGS " \
    -D__STARTUP_CLEAR_BSS \
    -mcpu=cortex-m33 \
    -mthumb \
    ${FPU} \
")

SET(C_COMMON_FLAGS " \
    -DCPU_MIMXRT595SFFOC_cm33 \
    -mcpu=cortex-m33 \
    -mthumb -nostdlib \
    -fno-common \
    -g3 \
    -Wall \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin-specs=nano.specs \
    -MMD \
    -MP \
    ${FPU} \
    -DVG_BLIT_WORKAROUND=0 \
")

SET(CXX_COMMON_FLAGS " \
    -DCPU_MIMXRT595SFFOC_cm33 \
    -mcpu=cortex-m33 \
    -mthumb -nostdlib \
    -fno-common \
    -g3 \
    -Wall \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin-specs=nano.specs \
    -MMD \
    -MP \
    ${FPU} \
    -DVG_BLIT_WORKAROUND=0 \
")

SET(EXE_LINKER_COMMON_FLAGS " \
    -Xlinker --gc-sections \
    -Xlinker -print-memory-usage \
    -Xlinker --sort-section=alignment \
    -Xlinker -Map=${ProjDirPath}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.map \
    -u _printf_float \
    -L${ProjDirPath} \
    -T${ProjDirPath}/mimxrt595_freertos-bsp_Debug.ld \
")

SET(CMAKE_ASM_FLAGS_DEBUG " \
    ${CMAKE_ASM_FLAGS_DEBUG} \
    ${ASM_COMMON_FLAGS} \
    -DDEBUG \
")

SET(CMAKE_C_FLAGS_DEBUG " \
    ${CMAKE_C_FLAGS_DEBUG} \
    ${C_COMMON_FLAGS} \
    -DDEBUG \
    -O0 \
")

SET(CMAKE_CXX_FLAGS_DEBUG " \
    ${CMAKE_CXX_FLAGS_DEBUG} \
    ${CXX_COMMON_FLAGS} \
    -DDEBUG \
    -O0 \
")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
    ${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
    ${EXE_LINKER_COMMON_FLAGS} \
")

SET(CMAKE_ASM_FLAGS_RELEASE " \
    ${CMAKE_ASM_FLAGS_RELEASE} \
    ${ASM_COMMON_FLAGS} \
    -DNDEBUG \
")

SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    ${C_COMMON_FLAGS} \
    -O3 \
")

SET(CMAKE_CXX_FLAGS_RELEASE " \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    ${CXX_COMMON_FLAGS} \
    -O3 \
")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    ${EXE_LINKER_COMMON_FLAGS} \
")
