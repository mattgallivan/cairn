cmake_minimum_required(VERSION 3.10)

project(CairnSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(log_sample log.cpp)
target_link_libraries(log_sample engine)

add_executable(main_sample main.cpp)
target_link_libraries(main_sample engine)

add_executable(time_sample time.cpp)
target_link_libraries(time_sample engine)

add_executable(window_sample window.cpp)
target_link_libraries(window_sample engine)
