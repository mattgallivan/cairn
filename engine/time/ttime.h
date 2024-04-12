#ifndef TIME_H
#define TIME_H

#include "buffer.h"

namespace Cairn {

class Time {

public:
  static void get_current_time(Buffer& buffer);
};

} // namespace Cairn

#endif // TIME_H
