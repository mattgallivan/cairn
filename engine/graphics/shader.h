#pragma once

#include "log.h"
#include "resource.h"

#include <GL/glew.h>

#include <fstream>
#include <sstream>

namespace Cairn {

/**
 * A shader is a GPU program containing a vertex and a fragment shader.
 * It must be loaded and built before being used.
 */
class Shader : public Resource {
public:
  ~Shader();

  /** Save the shader to a file. */
  bool save(const std::string& file_path) const override;

  /** Load the shader from a file. */
  bool load(const std::string& file_path) override;

  /** Build the shader. */
  bool build();

  /** Set a uniform value. */
  template <typename T>
  void set_uniform(const std::string& name, const T& value);

  /** Use the shader. */
  void use();

private:
  /** Compile the shaders and the shader program. */
  GLuint compile(GLenum type, const std::string& source);

  /** The shader program's ID. */
  GLuint program_id;

  /** The fragment shader's source code. */
  std::string fragment_source;

  /** The vertex shader's source code. */
  std::string vertex_source;
};

} // namespace Cairn
