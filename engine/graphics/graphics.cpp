#include "graphics.h"

#include "log.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>

namespace Cairn {

Graphics::Graphics(Window& window) {
  glfwMakeContextCurrent(window.get_glfw_window());
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    Log::error(Log::Category::Graphics, "Failed to initialize GLEW");
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

  GLenum format = texture.num_channels == 4 ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, texture.data);
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

void Graphics::draw(Shader& shader, Camera& camera, std::vector<Sprite>& sprites) {
  glUseProgram(programs[shader.id]);

  std::stable_sort(sprites.begin(), sprites.end(), [](const Cairn::Sprite& a, const Cairn::Sprite& b) {
    return static_cast<int>(a.layer) < static_cast<int>(b.layer);
  });

  GLuint uniform_projection = glGetUniformLocation(programs[shader.id], "projection");
  glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(camera.projection));

  for (auto& sprite : sprites) {
    glBindVertexArray(meshes[sprite.mesh->get_id()]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[sprite.texture->id]);
    glUniform1i(glGetUniformLocation(programs[shader.id], "tex"), 0);

    GLuint uniform_model = glGetUniformLocation(programs[shader.id], "model");
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(sprite.get_model_matrix()));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
  }
}

} // namespace Cairn
