#pragma once

#include "ui_image.h"
#include "ui_label.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

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
  UIManager();

  void render(UIImage image);

  void render(UILabel label);

private:
  GLuint compile_shader(GLenum type, const char* source);

  GLuint create_shader_program(const char* vertex_source, const char* fragment_source);

  std::unordered_map<GLchar, Character> characters;

  GLuint vao, vbo;

  GLuint shader_program;
};

} // namespace Cairn
