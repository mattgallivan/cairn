#pragma once

#include <string>

namespace Cairn {

/** A shader consisting of a vertex and a fragment shader. */
class Shader {

public:
  Shader(const std::string& vertex_source, const std::string& fragment_source)
      : vertex_source(vertex_source), fragment_source(fragment_source) {
    static unsigned int counter = 0;
    id = "Shader_" + std::to_string(counter++);
  }

  /** The source code of the vertex shader. */
  std::string vertex_source;

  /** The source code of the fragment shader. */
  std::string fragment_source;

  /** The unique identifier of the shader. */
  std::string id;
};

} // namespace Cairn
