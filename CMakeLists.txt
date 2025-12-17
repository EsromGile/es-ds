cmake_minimum_required(VERSION 4.0)
project(em_ds C)

set(CMAKE_C_STANDARD 11)

add_library(em_ds STATIC
        src/em_string.c
        src/em_slice.c
        src/em_iterator.c
        src/em_string_builder.c
        src/em_hash.c)

target_include_directories(em_ds PUBLIC src include src/private)

find_library(MYLIBRARY_PATH NAMES em_allocators PATHS /usr/local/lib)

target_link_libraries(em_ds ${MYLIBRARY_PATH} m)

option(EM_DS_BUILD_TESTS "Build test executables" ON)
if(EM_DS_BUILD_TESTS)
    add_subdirectory(test)
endif()
