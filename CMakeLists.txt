cmake_minimum_required(VERSION 3.10)

project(Cairn)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENGINE_SOURCES
  engine/graphics/graphics.cpp
  engine/graphics/sprite.cpp
  engine/image/image.cpp
  engine/input/input_manager.cpp
  engine/input/input_profile.cpp
  engine/log/log.cpp
  engine/memory/memory.cpp
  engine/resource/resource.cpp
  engine/time/ttime.cpp
  engine/ui/ui_manager.cpp
  engine/window/window.cpp
)

add_library(engine ${ENGINE_SOURCES})

target_link_libraries(engine PUBLIC
  ${FREETYPE_LIBRARIES}
  ${GLEW_LIBRARIES}
  glfw
  OpenGL::GL
  ${X11_LIBRARIES}
  stdc++fs
)

include_directories(${PROJECT_SOURCE_DIR}/lib)

target_include_directories(engine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/graphics
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/image
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/input
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/io
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/log
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/memory
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/resource
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/time
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/ui
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/window
  ${FREETYPE_INCLUDE_DIRS}
)

add_subdirectory(samples)
enable_testing()
add_subdirectory(tests)
