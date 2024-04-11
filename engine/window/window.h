#ifndef WINDOW_H
#define WINDOW_H

#ifdef __linux__
#include "window_x11.h"
#endif

namespace Cairn {

#ifdef __linux__
using Window = Window_X11;
#endif

} // namespace Cairn

#endif // WINDOW_H
