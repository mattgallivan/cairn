#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Cairn {

Shader::~Shader() {
  if (program_id) {
    glDeleteProgram(program_id);
  }
}

bool Shader::save(const std::string& file_path) const {
  std::ofstream file(file_path);
  if (file) {
    file << "// Vertex Shader\n" << vertex_source << "\n\n// Fragment Shader\n" << fragment_source;
    return true;
  }
  Log::error(Log::Category::Graphics, "Failed to save shader to file: " + file_path);
  return false;
}

bool Shader::load(const std::string& file_path) {
  std::ifstream file(file_path);
  std::string line;
  std::string* current = nullptr;

  if (file) {
    while (getline(file, line)) {
      if (line.find("#shader vertex") != std::string::npos) {
        current = &vertex_source;
      } else if (line.find("#shader fragment") != std::string::npos) {
        current = &fragment_source;
      } else if (current) {
        *current += line + "\n";
      }
    }
    return true;
  }

  Log::error(Log::Category::Graphics, "Failed to load shader from file: " + file_path);
  return false;
}

bool Shader::build() {
  GLuint vertex_shader = compile(GL_VERTEX_SHADER, vertex_source);
  GLuint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_source);

  if (!vertex_shader || !fragment_shader) {
    return false;
  }

  program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader);
  glAttachShader(program_id, fragment_shader);

  glLinkProgram(program_id);

  GLint success;
  glGetProgramiv(program_id, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
    glGetProgramInfoLog(program_id, 512, nullptr, info_log);
    Log::error(Log::Category::Graphics, "Shader linking failed: " + std::string(info_log));
    return false;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return true;
}

template <>
void Shader::set_uniform<int>(const std::string& name, const int& value) {
  int location = glGetUniformLocation(program_id, name.c_str());
  glUniform1i(location, value);
}
template void Shader::set_uniform<int>(const std::string& name, const int& value);

template <>
void Shader::set_uniform<float>(const std::string& name, const float& value) {
  int location = glGetUniformLocation(program_id, name.c_str());
  glUniform1f(location, value);
}
template void Shader::set_uniform<float>(const std::string& name, const float& value);

template <>
void Shader::set_uniform<glm::vec3>(const std::string& name, const glm::vec3& value) {
  int location = glGetUniformLocation(program_id, name.c_str());
  glUniform3fv(location, 1, glm::value_ptr(value));
}
template void Shader::set_uniform<glm::vec3>(const std::string& name, const glm::vec3& value);

template <>
void Shader::set_uniform<glm::mat4>(const std::string& name, const glm::mat4& value) {
  int location = glGetUniformLocation(program_id, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template void Shader::set_uniform<glm::mat4>(const std::string& name, const glm::mat4& value);

void Shader::use() { glUseProgram(program_id); }

GLuint Shader::compile(GLenum type, const std::string& source) {
  GLuint shader = glCreateShader(type);
  const GLchar* src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(shader, 512, nullptr, info_log);
    Log::error(Log::Category::Graphics, std::string("Shader compilation failed: ") + info_log);
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

} // namespace Cairn
