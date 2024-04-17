#pragma once

#include "resource.h"

#include <vector>

#include <glm/glm.hpp>

namespace Cairn {

class Mesh : public Resource {

public:
  bool save(const std::string& file_path) const override;
  bool load(const std::string& file_path) override;

  std::vector<glm::vec2> vertices;

  std::vector<unsigned int> indices;

  std::vector<glm::vec2> texture_coordinates;

  std::vector<glm::vec3> colors;

  std::vector<glm::vec3> normals;
};

} // namespace Cairn
