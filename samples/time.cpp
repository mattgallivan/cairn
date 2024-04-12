#include "buffer.h"
#include "ttime.h"
#include "types.h"

int main() {
  Cairn::Byte data[64];
  Cairn::Buffer buffer(data, sizeof(data));
  Cairn::Time::get_current_time(buffer);
  return 0;
}
