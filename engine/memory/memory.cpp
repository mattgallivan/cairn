#include "memory.h"

namespace Cairn {

StackAllocator::StackAllocator(Size size) {
  memory = static_cast<Byte*>(malloc(size));
  pointer = memory;
  stack_size = size;
}

StackAllocator::~StackAllocator() { free(memory); }

void* StackAllocator::allocate(Size size) {
  if (pointer + size > memory + stack_size) {
    return nullptr;
  }
  void* result = pointer;
  pointer += size;
  return result;
}

void StackAllocator::deallocate(void* pointer) {}

void StackAllocator::reset() { pointer = memory; }

}; // namespace Cairn
