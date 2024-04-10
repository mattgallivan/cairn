#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

namespace Cairn {

class Allocator {
public:
  virtual ~Allocator() = default;

  virtual void* allocate(Size size) = 0;
  virtual void deallocate(void* pointer) = 0;
  virtual void reset() = 0;
};

class StackAllocator : public Allocator {
public:
  StackAllocator(Size size);
  ~StackAllocator();

  void* allocate(Size size) override;
  void deallocate(void* pointer) override;
  void reset() override;

private:
  Byte* memory;
  Byte* pointer;
  Size stack_size;
};

} // namespace Cairn

#endif // MEMORY_H
