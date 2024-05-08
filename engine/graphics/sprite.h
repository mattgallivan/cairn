#pragma once

#include "mesh.h"
#include "texture.h"

#include <glm/glm.hpp>

namespace Cairn {

class Sprite {

public:
  Sprite(Mesh& mesh, Texture& texture) : mesh(mesh), texture(texture) {}

  glm::mat4 get_model_matrix() const;

  Mesh& mesh;

  Texture& texture;

  glm::vec2 position = glm::vec2(0.0f, 0.0f);

  glm::vec2 rotation = glm::vec2(0.0f, 0.0f);

  glm::vec2 scale = glm::vec2(1.0f, 1.0f);
};

} // namespace Cairn
