cmake_minimum_required(VERSION 2.8)

project(MultiCast)

find_package(Threads REQUIRED)

option(BEAGLE "Whether we are compiling for BeagleBone" OFF)

set(Beagle_SOURCES
    adc.cpp
    subroutine_adc.cpp
    subroutine_gpio.cpp
    main_beagle.cpp)

set(App_SOURCES
    main_app.cpp)

add_executable(beagle ${Beagle_SOURCES})
add_executable(app ${App_SOURCES})

target_link_libraries(beagle
    -lpthread)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

if(BEAGLE)
    add_definitions(-DBEAGLE)
endif()
