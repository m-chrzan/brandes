cmake_minimum_required(VERSION 3.5)
project(brandes CXX)

find_package ( Threads REQUIRED )

set(CMAKE_CXX_FLAGS "-std=c++14 -O3")

set(SOURCE_FILES src/brandes.cc
                 src/parse.h
                 src/graph.h
                 src/dependency_calculator.h)

add_executable(brandes ${SOURCE_FILES})
target_link_libraries(brandes ${CMAKE_THREAD_LIBS_INIT} )
