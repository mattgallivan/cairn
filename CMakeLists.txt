cmake_minimum_required(VERSION 3.10)

project(Cairn)

find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENGINE_SOURCES
  engine/memory/memory.cpp
  engine/window/window_x11.cpp
)

add_library(engine ${ENGINE_SOURCES})

target_link_libraries(engine ${X11_LIBRARIES})

target_include_directories(engine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/memory
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/window
)

add_subdirectory(samples)
enable_testing()
add_subdirectory(test)
