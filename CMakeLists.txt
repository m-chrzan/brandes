cmake_minimum_required(VERSION 3.5)
project(brandes CXX)

option(DEBUG OFF)

if (DEBUG)
    set(CMAKE_BUILD_TYPE DEBUG)
else (DEBUG)
    set(CMAKE_BUILD_TYPE RELEASE)
endif (DEBUG)

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")
set(CMAKE_CXX_FLAGS_RELASE "-O3")

set(SOURCE_FILES src/brandes.cc
                 src/parse.h
                 src/graph.h)

add_executable(brandes ${SOURCE_FILES})
