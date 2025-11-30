cmake_minimum_required(VERSION 4.0)
project(em_ds C)

set(CMAKE_C_STANDARD 11)

add_library(em_ds SHARED
        string.c
        string.h)

add_executable(em_ds_test main.c)
target_link_libraries(em_ds_test PRIVATE em_ds)
