#pragma once

#include "mesh.h"

#include <glm/glm.hpp>

namespace Cairn {

class Sprite {

public:
  Sprite(Mesh& mesh, const glm::mat4 transform) : mesh(mesh), transform(transform) {}

  Mesh& mesh;

  const glm::mat4 transform;
};

} // namespace Cairn
