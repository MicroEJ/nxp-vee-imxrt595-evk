SET CMD=ninja

if not exist debug mkdir debug
cd debug
cmake --preset debug ..
%CMD%

if not exist release mkdir release
cd release
cmake --preset release ..
%CMD%
