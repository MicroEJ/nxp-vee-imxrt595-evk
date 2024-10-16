SET CMD=ninja

if not exist debug mkdir debug
cd debug
cmake -DCMAKE_TOOLCHAIN_FILE="../../../mcux-sdk/core/tools/cmake_toolchain_files/armgcc.cmake" -G "%FLAVOUR%" -DCMAKE_BUILD_TYPE=debug ..
%CMD%
