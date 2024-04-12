#ifndef BUFFER_H
#define BUFFER_H

#include "types.h"

namespace Cairn {

class Buffer {

public:
  Buffer(Byte* data, Size size) : data(data), size(size){};
  Buffer(const Buffer& other) = default;
  Buffer& operator=(const Buffer& other) = default;

  Byte* data;
  Size size;
};

} // namespace Cairn

#endif // BUFFER_H
