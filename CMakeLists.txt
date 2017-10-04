cmake_minimum_required(VERSION 3.8)
project(libt4)

file(GLOB t4_src
    "src/T4Loader/*.h"
    "src/T4Loader/*.cpp"
)

add_library(t4 ${t4_src})

target_include_directories(t4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
