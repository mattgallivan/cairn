#pragma once

#include <string>

namespace Cairn {

class Shader {

public:
  Shader(const std::string& vertex_source, const std::string& fragment_source)
      : vertex_source(vertex_source), fragment_source(fragment_source) {}

  std::string vertex_source;
  std::string fragment_source;

  std::string id = "SHADER_ID";
};

} // namespace Cairn
