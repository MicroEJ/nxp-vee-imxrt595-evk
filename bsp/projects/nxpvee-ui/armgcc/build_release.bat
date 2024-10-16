SET CMD=ninja

if not exist release mkdir release
cd release
cmake -DCMAKE_TOOLCHAIN_FILE="../../../mcux-sdk/core/tools/cmake_toolchain_files/armgcc.cmake" -G "%FLAVOUR%" -DCMAKE_BUILD_TYPE=release ..
%CMD%
