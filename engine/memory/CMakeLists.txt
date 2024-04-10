add_library(memory
  types.h
  memory.h
  memory.cpp
)

target_include_directories(memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
