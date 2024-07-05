#include "graphics.h"

#include "log/log.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <string>

#include <iostream>

namespace Cairn::Graphics {

Graphics::Graphics(Window::Window& window) {
  glfwMakeContextCurrent(window.get_glfw_window());
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::string message = std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));
    Log::error(Log::Category::Graphics, "Failed to initialize GLEW: " + message);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Graphics::~Graphics() {
  for (auto& mesh : meshes) {
    glDeleteVertexArrays(1, &mesh.second);
  }

  for (auto& texture : textures) {
    glDeleteTextures(1, &texture.second);
  }

  for (auto& program : programs) {
    glDeleteProgram(program.second);
  }
}

bool Graphics::build(Mesh& mesh) {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  std::vector<GLfloat> vertices;
  vertices.reserve(mesh.vertices.size() * 5);
  for (size_t i = 0; i < mesh.vertices.size(); i++) {
    vertices.push_back(mesh.vertices[i].x);
    vertices.push_back(mesh.vertices[i].y);
    vertices.push_back(0.f);
    vertices.push_back(mesh.texture_coordinates[i].x);
    vertices.push_back(mesh.texture_coordinates[i].y);
  }

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  meshes[mesh.id] = vao;

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
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
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
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
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
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
    return false;
  }

  programs[shader.id] = program;

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return true;
}

void Graphics::draw(Shader& shader, Camera& camera, std::vector<Sprite*>& sprites) {
  if (programs.find(shader.id) == programs.end()) {
    Log::error(Log::Category::Graphics, "Shader program not found.");
    return;
  }

  glUseProgram(programs[shader.id]);

  std::stable_sort(sprites.begin(), sprites.end(), [](const Cairn::Sprite* a, const Cairn::Sprite* b) {
    return static_cast<int>(a->layer) < static_cast<int>(b->layer);
  });

  GLuint uniform_projection = glGetUniformLocation(programs[shader.id], "projection");
  glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));

  for (auto& sprite : sprites) {
    // If the mesh hasn't been built, build it.
    if (meshes.find(sprite->mesh->id) == meshes.end()) {
      build(*sprite->mesh);
    }

    glBindVertexArray(meshes[sprite->mesh->id]);

    // If the texture hasn't been built, build it.
    if (textures.find(sprite->texture->id) == textures.end()) {
      build(*sprite->texture);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[sprite->texture->id]);
    glUniform1i(glGetUniformLocation(programs[shader.id], "tex"), 0);

    GLuint uniform_model = glGetUniformLocation(programs[shader.id], "model");
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(sprite->get_model()));

    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}

void Graphics::draw(Shader& shader, Camera& camera, Tilemap& tilemap) {
  if (programs.find(shader.id) == programs.end()) {
    Log::error(Log::Category::Graphics, "Shader program not found.");
    return;
  }

  glUseProgram(programs[shader.id]);

  GLuint uniform_projection = glGetUniformLocation(programs[shader.id], "projection");
  glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));

  GLuint uniform_model = glGetUniformLocation(programs[shader.id], "model");

  Mesh mesh;
  build(mesh);

  glBindVertexArray(meshes[mesh.id]);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 4, nullptr,
               GL_DYNAMIC_DRAW); // Allocate buffer for 4 vertices with 8 properties each

  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  // Texture coordinate attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  int atlas_rows = tilemap.atlas->height / tilemap.atlas->tile_height;
  int atlas_cols = tilemap.atlas->width / tilemap.atlas->tile_width;

  for (int y = 0; y < tilemap.height; y++) {
    for (int x = 0; x < tilemap.width; x++) {
      int tile_index = tilemap.data[y * tilemap.width + x];

      int atlas_x = tile_index % atlas_cols;
      int atlas_y = tile_index / atlas_cols;

      float s_min = (float)atlas_x / atlas_cols;
      float s_max = (float)(atlas_x + 1) / atlas_cols;
      float t_min = (float)atlas_y / atlas_rows;
      float t_max = (float)(atlas_y + 1) / atlas_rows;

      GLfloat vertices[] = {
          // Triangle 1
          0.0f, 1.0f, s_min, t_min, // Top-left
          0.0f, 0.0f, s_min, t_max, // Bottom-left
          1.0f, 1.0f, s_max, t_min, // Top-right
          // Triangle 2
          0.0f, 0.0f, s_min, t_max, // Bottom-left
          1.0f, 0.0f, s_max, t_max, // Bottom-right
          1.0f, 1.0f, s_max, t_min, // Top-right
      };

      // Update the vertex buffer here, particularly the texture coordinates
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

      // If the texture hasn't been built, build it.
      if (textures.find(tilemap.atlas->id) == textures.end()) {
        build(*tilemap.atlas);
      }

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textures[tilemap.atlas->id]);
      glUniform1i(glGetUniformLocation(programs[shader.id], "tex"), 0);

      glm::mat4 model =
          glm::translate(glm::mat4(1.0f), glm::vec3(x * tilemap.tile_width, y * tilemap.tile_height, 0.0f));
      model = glm::translate(model, glm::vec3(tilemap.position, 0.f));
      model = glm::scale(model, glm::vec3(tilemap.tile_width, tilemap.tile_height, 1.0f));
      glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

      glDrawArrays(GL_TRIANGLES, 0, 6);

      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }

  glDeleteBuffers(1, &vbo);
}

void Graphics::draw(Image* image) const {
  if (!image || !image->pixels) {
    Log::error(Log::Category::Graphics, "Image is null or has no pixels.");
    return;
  }

  // Shader source code
  const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;
    layout(location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
        TexCoord = aTexCoord;
    }
    )";

  const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    in vec2 TexCoord;

    uniform sampler2D texture1;

    void main() {
        FragColor = texture(texture1, TexCoord);
    }
    )";

  // Compile and link shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Load and create a texture
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, image->num_channels == 4 ? GL_RGBA : GL_RGB, image->width, image->height, 0,
               image->num_channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Vertex data
  float vertices[] = {
      // positions    // texCoords
      -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
      1.0f,  -1.0f, 1.0f, 0.0f, // bottom right
      1.0f,  1.0f,  1.0f, 1.0f, // top right
      -1.0f, 1.0f,  0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
      0, 1, 2, // first triangle
      2, 3, 0  // second triangle
  };

  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

  glUseProgram(shaderProgram);

  // Draw
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Cleanup
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteTextures(1, &textureID);
  glDeleteProgram(shaderProgram);
}

} // namespace Cairn::Graphics
