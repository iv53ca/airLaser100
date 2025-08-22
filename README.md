Компиляция .exe с MacOS:
1. mkdir build-windows
2. cd build-windows
3. SDKROOT= MACOSX_DEPLOYMENT_TARGET= \
   cmake .. -G "Unix Makefiles" \
   -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw64.cmake \
   -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY
4. make -j

Компиляция .exe с Windows (не проверена):
0. pacman -S --needed mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make
1. mkdir build-mingw
2. cd build-mingw
3. cmake .. -G "MinGW Makefiles"
4. mingw32-make -j