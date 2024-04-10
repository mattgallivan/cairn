find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../engine)

add_executable(memory_test memory/memory.cpp)

target_link_libraries(memory_test ${GTEST_LIBRARIES} memory)

add_test(NAME memory_test COMMAND memory_test)
