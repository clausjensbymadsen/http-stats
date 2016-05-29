cmake_minimum_required(VERSION 3.5)
project(HttpStatsTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories("../include")
include_directories("../src")

set(SOURCE_FILES convert.cpp parser.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests ${CMAKE_CURRENT_SOURCE_DIR}/../lib/gtest_main.a)