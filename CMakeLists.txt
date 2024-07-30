cmake_minimum_required(VERSION 3.10)

project(Cairn)

# Set CMake policies and preferences
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
endif()

# Find packages

# Download and configure GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

# Include directories for libraries
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine)
include_directories(${FREETYPE_INCLUDE_DIRS})

# Source files (commented out for now)
set(ENGINE_SOURCES
  engine/animation/animation.cpp
  engine/animation/node.cpp
  engine/animation/system.cpp

  engine/ecs/entity.cpp
  engine/ecs/system.cpp

  engine/graphics/graphics.cpp
  engine/graphics/image.cpp
  engine/graphics/sprite.cpp

  engine/input/input_manager.cpp
  engine/input/input_profile.cpp

  engine/log/log.cpp

  engine/resource/resource.cpp

  engine/window/window.cpp
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

# --- SAMPLES ---

set(SAMPLE_SOURCES
  samples/animation.cpp
  samples/audio.cpp
)

foreach(SAMPLE_SOURCE ${SAMPLE_SOURCES})
  get_filename_component(SAMPLE_NAME ${SAMPLE_SOURCE} NAME_WE)
  add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE})
  target_link_libraries(${SAMPLE_NAME} PRIVATE engine)
endforeach()

# --- TESTS ---

enable_testing()

set(TEST_SOURCES
  tests/animation/test_animation.cpp
  tests/ecs/test_ecs.cpp
  tests/resource/test_resource.cpp
)

add_executable(tests ${TEST_SOURCES})

target_include_directories(tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/engine
  ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(tests PRIVATE
  engine
  GTest::gtest_main  
)

add_test(NAME ECSTEST COMMAND tests)
