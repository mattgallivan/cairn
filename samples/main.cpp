#include "mesh.h"

#include <iostream>

int main() {
  std::string file_path = "../resources/meshes/square.mesh";
  Cairn::Mesh mesh;
  mesh.load(file_path);
  std::cout << "Mesh loaded from " << file_path << std::endl;
  std::cout << "Vertices: " << mesh.vertices.size() << std::endl;
  std::cout << "Indices: " << mesh.indices.size() << std::endl;
  std::cout << "Normals: " << mesh.normals.size() << std::endl;
  std::cout << "TexCoords: " << mesh.texture_coordinates.size() << std::endl;
  std::cout << "Colors: " << mesh.colors.size() << std::endl;
  return 0;
}
