#pragma once

#include "mesh.h"
#include "texture.h"

#include <glm/glm.hpp>

namespace Cairn {

class Sprite {

public:
  Sprite(Mesh& mesh, Texture& texture, const glm::mat4 transform)
      : mesh(mesh), texture(texture), transform(transform) {}

  Mesh& mesh;

  const glm::mat4 transform;

  Texture& texture;
};

} // namespace Cairn
