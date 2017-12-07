cmake_minimum_required(VERSION 2.8)

project(MultiCast)

find_package(Threads REQUIRED)

option(BEAGLE "Whether we are compiling for BeagleBone" OFF)

set(Multicast_SOURCES
    multicast_sender.cpp
    multicast_receiver.cpp)

set(Beagle_SOURCES
    subroutine_adc.cpp
    subroutine_gpio.cpp
    main_beagle.cpp)

if(BEAGLE)
    add_definitions(-DBEAGLE)

    list(APPEND Beagle_SOURCES
         adc_beagle.cpp)
else()
    list(APPEND Beagle_SOURCES
         adc_fake.cpp)
endif()

set(App_SOURCES
    main_app.cpp)

add_library(multicast ${Multicast_SOURCES})
add_executable(beagle ${Beagle_SOURCES})
add_executable(app ${App_SOURCES})

target_link_libraries(beagle multicast -lpthread)
target_link_libraries(app multicast)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()
