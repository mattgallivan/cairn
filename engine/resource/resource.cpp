#include "resource.h"

#include "log.h"

#include <fstream>
#include <iostream>

namespace Cairn {

int Resource::next_id = 0;

std::string Resource::load_shader(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    Log::error(Log::Category::Resource, "Failed to load shader file: " + file_path);
    return nullptr;
  }

  std::string shader_code;
  std::string line;
  while (std::getline(file, line)) {
    shader_code += line + "\n";
  }
  file.close();

  return shader_code;
}

} // namespace Cairn
