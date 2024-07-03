#include "window.h"

#include "log/log.h"

#include <iostream>

namespace Cairn::Window {

Window::Window(int width, int height, std::string title) {
  this->width = width;
  this->height = height;
  this->title = title;

  if (!glfwInit()) {
    Log::error(Log::Category::Window, "Failed to initialize GLFW");
    exit(1);
  }

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    Log::error(Log::Category::Window, "Failed to create window");
    glfwTerminate();
    exit(1);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, mouse_position_callback);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetWindowUserPointer(window, this);
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

GLFWwindow* Window::get_glfw_window() const { return window; }

bool Window::is_open() const { return !glfwWindowShouldClose(window); }

void Window::add_resize_callback(std::function<void(int, int)> callback) { resize_callbacks.push_back(callback); }

void Window::bind(InputManager* input_manager) {
  if (!input_manager) {
    Log::error(Log::Category::Window, "Cannot bind a null input manager to a window");
    return;
  }

  input_managers.insert(input_manager);
}

void Window::close() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

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

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);

  // Trigger all the resize callbacks.
  auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (!win) {
    Log::error(Log::Category::Window, "Failed to get window user pointer");
    return;
  }

  win->width = width;
  win->height = height;

  for (auto& callback : win->resize_callbacks) {
    callback(width, height);
  }
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (!win) {
    Log::error(Log::Category::Window, "Failed to get window user pointer");
    return;
  }

  Cairn::KeyboardEvent::Key ckey = static_cast<Cairn::KeyboardEvent::Key>(key);
  Cairn::InputEvent::State cstate = static_cast<Cairn::InputEvent::State>(action);

  KeyboardEvent event(ckey, cstate);
  for (auto& input_manager : win->input_managers) {
    input_manager->send(event);
  }
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (!win) {
    Log::error(Log::Category::Window, "Failed to get window user pointer");
    return;
  }

  // Convert GLFW button to Cairn button.
  Cairn::MouseButtonEvent::MouseButton cbutton = static_cast<Cairn::MouseButtonEvent::MouseButton>(button);
  Cairn::InputEvent::State cstate = static_cast<Cairn::InputEvent::State>(action);

  MouseButtonEvent event(cbutton, cstate);

  // Get the mouse position.
  double xpos, ypos;
  glfwGetCursorPos(window, &event.x, &event.y);

  // Flip the y coordinate.
  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  event.y = fb_height - event.y;

  for (auto& input_manager : win->input_managers) {
    input_manager->send(event);
  }
}

void Window::mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
  Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (!win) {
    Log::error(Log::Category::Window, "Failed to get window user pointer");
    return;
  }

  MousePositionEvent event(xpos, ypos);
  for (auto& input_manager : win->input_managers) {
    input_manager->send(event);
  }
}

} // namespace Cairn::Window
