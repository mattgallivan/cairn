#ifndef TTIME_H
#define TTIME_H

#include "buffer.h"

namespace Cairn {

class Time {

public:
  static void get_current_time(Buffer& buffer);
};

} // namespace Cairn

#endif // TTIME_H
