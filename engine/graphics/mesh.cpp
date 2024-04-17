#include "mesh.h"

#include "log.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Cairn {

bool Mesh::load(const std::string& file_path) {
  state = State::Loading;

  std::ifstream file(file_path);
  if (!file.is_open()) {
    Log::error(Log::Category::Graphics, "Failed to open file: " + file_path);
    state = State::Failed;
    return false;
  }

  std::string line;
  while (getline(file, line)) {
    line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // Trim leading whitespace
    line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // Trim trailing whitespace

    if (line.empty()) {
      continue;
    }

    std::istringstream iss(line);
    char type;
    iss >> type;

    if (type == 'v') { // Vertex
      glm::vec2 vertex;
      iss >> vertex.x >> vertex.y;
      vertices.push_back(vertex);
    } else if (type == 't') { // Texture coordinate
      glm::vec2 texCoord;
      iss >> texCoord.x >> texCoord.y;
      texture_coordinates.push_back(texCoord);
    } else if (type == 'c') { // Color
      glm::vec3 color;
      iss >> color.r >> color.g >> color.b;
      colors.push_back(color);
    } else if (type == 'n') { // Normal
      glm::vec3 normal;
      iss >> normal.x >> normal.y >> normal.z;
      normals.push_back(normal);
    } else if (type == 'i') { // Index
      unsigned int index;
      iss >> index;
      indices.push_back(index);
    }
  }

  file.close();
  state = State::Loaded;
  return true;
}

bool Mesh::save(const std::string& file_path) const {
  std::ofstream file(file_path, std::ios::out);
  if (!file.is_open()) {
    Log::error(Log::Category::Graphics, "Failed to open file: " + file_path);
    return false;
  }

  for (const auto& vertex : vertices) {
    file << "v " << vertex.x << " " << vertex.y << std::endl;
  }
  for (const auto& texCoord : texture_coordinates) {
    file << "t " << texCoord.x << " " << texCoord.y << std::endl;
  }
  for (const auto& color : colors) {
    file << "c " << color.r << " " << color.g << " " << color.b << std::endl;
  }
  for (const auto& normal : normals) {
    file << "n " << normal.x << " " << normal.y << " " << normal.z << std::endl;
  }
  for (const auto& index : indices) {
    file << "i " << index << std::endl;
  }

  file.close();
  return true;
}

} // namespace Cairn
