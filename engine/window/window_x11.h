#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include <X11/Xlib.h>

#include <../memory/types.h>

namespace Cairn {

class Window_X11 {

public:
  Window_X11(U32 width, U32 height, const Char* title);
  ~Window_X11();

  void poll();
  void set_fullscreen(Bool is_fullscreen);
  void set_size(U32 width, U32 height);
  void set_title(const Char* title);
  void set_visible(Bool is_visible);

protected:
  U32 width;
  U32 height;
  const Char* title;

private:
  Display* display;
  I32 screen;
  Window root;
  Window window;
};

} // namespace Cairn

#endif // WINDOW_X11_H
