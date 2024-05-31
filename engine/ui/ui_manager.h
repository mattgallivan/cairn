#pragma once

#include "shader.h"
#include "ui_image.h"
#include "ui_label.h"
#include "window.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>

namespace Cairn {

struct Character {
  unsigned int texture_id;
  glm::ivec2 size;
  glm::ivec2 bearing;
  unsigned int advance;
};

class UIManager {

public:
  UIManager(Window* window);

  ~UIManager();

  void render(UIImage image);

  void render(UILabel label);

private:
  GLuint compile_shader(GLenum type, const char* source);

  GLuint create_shader_program(Shader* shader);

  std::unordered_map<GLchar, Character> characters;  

  GLuint vao, vbo;

  GLuint image_shader_program, text_shader_program;

  std::unique_ptr<Shader> image_shader;
  std::unique_ptr<Shader> text_shader;

  Window* window;
};

} // namespace Cairn
