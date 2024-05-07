#include "graphics.h"

#include "log.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Cairn {

Graphics::Graphics(Window& window) {
  glfwMakeContextCurrent(window.get_glfw_window());
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    Log::error(Log::Category::Graphics, "Failed to initialize GLEW");
  }
}

bool Graphics::build(Mesh& mesh) {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  GLfloat vertices[] = {
      // First triangle
      0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // Top Right
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom Right
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Top Left

      // Second triangle
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom Right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // Top Left
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  meshes[mesh.get_id()] = vao;

  return true;
}

bool Graphics::build(Texture& texture) {
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
  textures[texture.id] = texture_id;

  glBindTexture(GL_TEXTURE_2D, 0);
  return true;
}

bool Graphics::compile(Shader& shader) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  const char* vertex_shader_source = shader.vertex_source.c_str();
  const char* fragment_shader_source = shader.fragment_source.c_str();

  glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
  glCompileShader(vertex_shader);

  GLint success;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
    Log::error(Log::Category::Graphics, "Failed to compile vertex shader.");
    Log::error(Log::Category::Graphics, info_log);
    return false;
  }

  glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
    Log::error(Log::Category::Graphics, "Failed to compile fragment shader.");
    Log::error(Log::Category::Graphics, info_log);
    return false;
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
    glGetProgramInfoLog(program, 512, nullptr, info_log);
    Log::error(Log::Category::Graphics, "Failed to link shader program.");
    Log::error(Log::Category::Graphics, info_log);
    return false;
  }

  programs[shader.id] = program;

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return true;
}

void Graphics::draw(Shader& shader, Sprite& sprite) {
  glUseProgram(programs[shader.id]);
  glBindVertexArray(meshes[sprite.mesh.get_id()]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[sprite.texture.id]);
  glUniform1i(glGetUniformLocation(programs[shader.id], "tex"), 0);

  GLuint uniform_model = glGetUniformLocation(programs[shader.id], "model");
  glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(sprite.transform));

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Cairn