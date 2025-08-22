set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER   /opt/homebrew/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER  /opt/homebrew/bin/x86_64-w64-mingw32-windres)
set(CMAKE_AR           /opt/homebrew/bin/x86_64-w64-mingw32-gcc-ar)
set(CMAKE_RANLIB       /opt/homebrew/bin/x86_64-w64-mingw32-gcc-ranlib)

set(CMAKE_OSX_ARCHITECTURES "" CACHE STRING "" FORCE)
set(CMAKE_OSX_SYSROOT       "" CACHE PATH   "" FORCE)
set(CMAKE_C_FLAGS           "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS         "" CACHE STRING "" FORCE)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)