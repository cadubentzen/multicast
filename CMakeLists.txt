cmake_minimum_required(VERSION 2.8)

project(MultiCast)

find_package(Threads REQUIRED)

option(BEAGLE "Whether we are compiling for BeagleBone" OFF)

include_directories(${CMAKE_SOURCE_DIR} adc gpio lcd multicast subroutines)

set(Multicast_SOURCES
    multicast/multicast_sender.cpp
    multicast/multicast_receiver.cpp)

set(Beagle_SOURCES
    adc/adc.cpp
    gpio/gpio.cpp
    lcd/lcd.cpp
    subroutines/subroutine_adc.cpp
    subroutines/subroutine_gpio.cpp
    main_beagle.cpp)

if(BEAGLE)
    add_definitions(-DBEAGLE)

    list(APPEND Beagle_SOURCES
         adc/adc_beagle.cpp
         gpio/gpio_beagle.cpp
         lcd/lcd_beagle.cpp)
else()
    list(APPEND Beagle_SOURCES
         adc/adc_fake.cpp
         gpio/gpio_fake.cpp
         lcd/lcd_fake.cpp)
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
