cmake_minimum_required(VERSION 3.16)
project(airLaserBackUp)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Old)

set(SOURCES
        main.cpp
        NMEAReader.cpp
        PcapReader.cpp
        positionPacket.cpp
        singleReturnPointPacket.cpp
        Old/MainFunc.cpp
        Old/gpsTimeMaker.cpp
        Old/packetDataClass.cpp
)
add_executable(airLaserBackUp ${SOURCES})

# TODO: личный реп + доступ Вадиму