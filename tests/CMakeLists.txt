cmake_minimum_required(VERSION 3.10)

project(CairnTests)

find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../engine)

add_executable(buffer_test memory/buffer.cpp)
target_link_libraries(buffer_test ${GTEST_LIBRARIES} engine)

add_executable(memory_test memory/memory.cpp)
target_link_libraries(memory_test ${GTEST_LIBRARIES} engine)

add_executable(time_test time/time.cpp)
target_link_libraries(time_test ${GTEST_LIBRARIES} engine)

add_executable(window_test window/window.cpp)
target_link_libraries(window_test ${GTEST_LIBRARIES} engine)

gtest_discover_tests(buffer_test)
gtest_discover_tests(memory_test)
gtest_discover_tests(time_test)
gtest_discover_tests(window_test)
