#include "memory.h"

namespace Cairn {

StackAllocator::StackAllocator(Size size) {
  memory = malloc(size);
  pointer = memory;
  stack_size = size;
}

StackAllocator::~StackAllocator() { free(memory); }

StackAllocator::allocate(Size size) {
  if (pointer + size > memory + stack_size) {
    return nullptr;
  }
  void* result = pointer;
  pointer += size;
  return result;
}

StackAllocator::deallocate(void* pointer) {}

StackAllocator::reset() { pointer = memory; }

}; // namespace Cairn
