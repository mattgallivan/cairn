#include <cstdio>
#include <ctime>
#include <sys/time.h>

#include "ttime.h"
#include "types.h"

namespace Cairn {

void Time::get_current_time(Buffer& buffer) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  struct tm* ptm = localtime(&tv.tv_sec);

  U8 max_str_length = 9;
  if (buffer.size >= max_str_length) {
    buffer.length = strftime(reinterpret_cast<Char*>(buffer.data), buffer.size,
                             "%H:%M:%S", ptm);
    if (buffer.length > 0 && buffer.length < buffer.size) {
      buffer.data[buffer.length] = '\0';
      buffer.length++;
    }
  }
}

} // namespace Cairn
