#pragma once

#include "mesh.h"

namespace Cairn {

class Sprite {

public:
  Sprite(Mesh& mesh) : mesh(mesh) {}

  Mesh& mesh;
};

} // namespace Cairn
