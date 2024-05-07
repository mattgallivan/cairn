#pragma once

#include "shader.h"
#include "sprite.h"
#include "texture.h"
#include "window.h"

#include <unordered_map>

namespace Cairn {

class Graphics {

public:
  Graphics(Window& window);

  bool build(Mesh& mesh);

  bool build(Texture& texture);

  bool compile(Shader& shader);

  void draw(Shader& shader, Sprite& sprite);

private:
  std::unordered_map<std::string, GLuint> meshes;

  std::unordered_map<std::string, GLuint> programs;

  std::unordered_map<std::string, GLuint> textures;
};

} // namespace Cairn
