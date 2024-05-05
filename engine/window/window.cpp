#include "window.h"

#include "log.h"

namespace Cairn {

Window::Window(int width, int height, const char* title) {
  this->width = width;
  this->height = height;
  this->title = title;

  if (!glfwInit()) {
    Log::error(Log::Category::Window, "Failed to initialize GLFW");
    exit(1);
  }

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    Log::error(Log::Category::Window, "Failed to create window");
    glfwTerminate();
    exit(1);
  }
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::is_open() const { return !glfwWindowShouldClose(window); }

void Window::hide() { glfwHideWindow(window); }

void Window::maximize() { glfwMaximizeWindow(window); }

void Window::minimize() { glfwIconifyWindow(window); }

void Window::refresh() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Window::set_cursor_visible(bool is_visible) {
  glfwSetInputMode(window, GLFW_CURSOR, is_visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
  this->is_cursor_visible = is_visible;
}

void Window::set_fullscreen(bool is_fullscreen) {
  if (is_fullscreen) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
  } else {
    glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
  }
  this->is_fullscreen = is_fullscreen;
}

void Window::show() { glfwShowWindow(window); }

} // namespace Cairn
