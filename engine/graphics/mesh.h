#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Cairn {

/**
 * A mesh is a collection of vertices, indices, texture coordinates, colors, and normals.
 * It is used to represent a 2D object in the scene.
 */
class Mesh {

public:
  Mesh() {
    static unsigned int counter = 0;
    id = "Mesh_" + std::to_string(counter++);
  }

  /** The vertices of the mesh. */
  std::vector<glm::vec2> vertices;

  /** The indices of the mesh used to draw the triangles. */
  std::vector<unsigned int> indices;

  /** The texture coordinates of the mesh. */
  std::vector<glm::vec2> texture_coordinates;

  /** The colors of the mesh. */
  std::vector<glm::vec3> colors;

  /** The normals of the mesh. */
  std::vector<glm::vec3> normals;

  /** The unique identifier of the mesh. */
  std::string id;
};

} // namespace Cairn
