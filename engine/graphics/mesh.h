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

    vertices = {
        {0.5f, 0.5f},   // Top Right
        {0.5f, -0.5f},  // Bottom Right
        {-0.5f, 0.5f},  // Top Left
        {0.5f, -0.5f},  // Bottom Right
        {-0.5f, -0.5f}, // Bottom Left
        {-0.5f, 0.5f}   // Top Left
    };

    texture_coordinates = {
        {1.0f, 0.0f}, // Top Right
        {1.0f, 1.0f}, // Bottom Right
        {0.0f, 0.0f}, // Top Left
        {1.0f, 1.0f}, // Bottom Right
        {0.0f, 1.0f}, // Bottom Left
        {0.0f, 0.0f}  // Top Left
    };

    indices = {0, 1, 2, 3, 4, 5};
  }

  /** The vertices of the mesh. */
  std::vector<glm::vec2> vertices;

  /** The indices of the mesh used to draw the triangles. */
  std::vector<unsigned int> indices;

  /** The texture coordinates of the mesh. */
  std::vector<glm::vec2> texture_coordinates;

  /** The unique identifier of the mesh. */
  std::string id;
};

} // namespace Cairn
