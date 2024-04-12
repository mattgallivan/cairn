#ifndef BUFFER_H
#define BUFFER_H

#include "types.h"

namespace Cairn {

class Buffer {

public:
  Buffer(Byte* data, Size size) : data(data), size(size){};
  Buffer(const Buffer& other) = default;
  Buffer& operator=(const Buffer& other) = default;

  Byte* data = nullptr;
  Size size = 0;
  Size length = 0;
};

} // namespace Cairn

#endif // BUFFER_H
