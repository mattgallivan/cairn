cmake_minimum_required(VERSION 3.10)

project(CairnSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main_sample main.cpp)
target_link_libraries(main_sample engine)

add_executable(animation_sample animation.cpp)
target_link_libraries(animation_sample engine)
