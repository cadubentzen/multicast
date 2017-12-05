cmake_minimum_required(VERSION 2.8)

project(MultiCast)

find_package(Threads REQUIRED)

option(BEAGLE "Whether we are compiling for BeagleBone" OFF)

set(MultiCast_SOURCES
    adc.cpp
    main_adc.cpp
    main_gpio.cpp
    main_app.cpp
    main.cpp)

add_executable(multicast ${MultiCast_SOURCES})

target_link_libraries(multicast
    -lpthread)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("DEBUG type")
    add_definitions(-DDEBUG)
endif()

if(BEAGLE)
    add_definitions(-DBEAGLE)
endif()
