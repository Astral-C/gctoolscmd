cmake_minimum_required(VERSION 3.8)
project(gctools)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/gctoolsplusplus)
add_subdirectory(lib/argparse)

file(GLOB_RECURSE GCTOOLSCMD_SRC
    "src/*.cpp"
    "src/*.c"
    "include/*.hpp"
    "include/*.h"
    "lib/gctoolsplusplus/lib/bstream.cpp"
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(gctools ${GCTOOLSCMD_SRC})
target_include_directories(gctools PUBLIC include lib/gctoolsplusplus/lib/bStream lib/gctoolsplusplus/include lib/argparse/include)
target_link_libraries(gctools gctools++ Qt6::Widgets)