cmake_minimum_required(VERSION 3.10)

project(Cairn)

# Set CMake policies and preferences
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages
find_package(GTest REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

# Include directories for libraries
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine)
include_directories(${FREETYPE_INCLUDE_DIRS})

# Source files (commented out for now)
set(ENGINE_SOURCES
  engine/engine.cpp
  # engine/graphics/graphics.cpp
#   engine/graphics/sprite.cpp
#   engine/image/image.cpp
#   engine/input/input_manager.cpp
#   engine/input/input_profile.cpp
#   engine/log/log.cpp
#   engine/memory/memory.cpp
#   engine/resource/resource.cpp
#   engine/time/ttime.cpp
#   engine/ui/ui_manager.cpp
#   engine/window/window.cpp
#   engine/animation/animation.cpp
)

# Create an empty engine library for now
add_library(engine ${ENGINE_SOURCES})

# Link libraries to the engine
target_link_libraries(engine PUBLIC
  ${FREETYPE_LIBRARIES}
  ${GLEW_LIBRARIES}
  glfw
  OpenGL::GL
  ${X11_LIBRARIES}
  stdc++fs
)

# Enable testing (if desired)
enable_testing()

set(TEST_SOURCES
  tests/test_animation.cpp
)

# Add the test executable (commented out for now)
add_executable(run_tests ${TEST_SOURCES})

# Include directories for tests
target_include_directories(run_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/engine
  ${GTEST_INCLUDE_DIRS}
)

# Link test executable with Google Test and the engine library
target_link_libraries(run_tests PRIVATE
  engine
  GTest::GTest
  GTest::Main
)

# Add tests (commented out for now)
add_test(NAME AnimationTests COMMAND run_tests)
