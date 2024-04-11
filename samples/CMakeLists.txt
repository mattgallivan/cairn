cmake_minimum_required(VERSION 3.10)

project(CairnSamples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(window_sample window.cpp)
target_link_libraries(window_sample engine)
