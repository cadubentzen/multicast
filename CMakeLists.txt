cmake_minimum_required(VERSION 3.5)

project(MultiCast)

find_package(Threads REQUIRED)

set(MultiCast_SOURCES
    adc_handle.cpp
    gpio_handle.cpp
    app_handle.cpp
    main.cpp)

add_executable(multicast ${MultiCast_SOURCES})

target_link_libraries(multicast
    -lpthread)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("DEBUG type")
    add_definitions(-DDEBUG)
endif()
