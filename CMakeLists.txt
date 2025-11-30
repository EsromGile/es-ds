cmake_minimum_required(VERSION 4.0)
project(em_ds C)

set(CMAKE_C_STANDARD 11)

add_library(em_ds STATIC
        src/string.c)

target_include_directories(em_ds PUBLIC src)

option(EM_DS_BUILD_TESTS "Build test executables" ON)
if(EM_DS_BUILD_TESTS)
    add_subdirectory(test)
endif()
