#include "ui_manager.h"

#include "log.h"
#include "resource.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Cairn {

UIManager::UIManager(Window* window) {
  this->window = window;

  // Load the shaders.
  image_shader = std::make_unique<Shader>(Resource::load_shader("../resources/shaders/ui/image.vert"),
                                          Resource::load_shader("../resources/shaders/ui/image.frag"));
  image_shader_program = create_shader_program(image_shader.get());

  text_shader = std::make_unique<Shader>(Resource::load_shader("../resources/shaders/ui/text.vert"),
                                         Resource::load_shader("../resources/shaders/ui/text.frag"));

  text_shader_program = create_shader_program(text_shader.get());

  // Load the font library and font.
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    Log::error(Log::Category::UI, "Could not init FreeType library.");
    return;
  }

  FT_Face face;
  if (FT_New_Face(ft, "../resources/fonts/playfair/PlayfairDisplayMedium-9YKZK.ttf", 0, &face)) {
    Log::error(Log::Category::UI, "Could not load font.");
    FT_Done_FreeType(ft);
    return;
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (unsigned char c = 0; c < 128; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      Log::error(Log::Category::UI, "Could not load glyph.");
      continue;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,
                 GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                           glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                           static_cast<unsigned int>(face->glyph->advance.x)};

    characters.insert(std::pair<char, Character>(c, character));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

UIManager::~UIManager() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

GLuint UIManager::compile_shader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);
  // Check for shader compile errors
  GLint success;
  GLchar info_log[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    Log::error(Log::Category::UI, "Shader compilation failed: " + std::string(info_log));
  }
  return shader;
}

GLuint UIManager::create_shader_program(Shader* shader) {
  GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, shader->vertex_source.c_str());
  GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, shader->fragment_source.c_str());

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  // Check for linking errors
  GLint success;
  GLchar info_log[512];
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    Log::error(Log::Category::UI, "Shader linking failed: " + std::string(info_log));
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}

void UIManager::render(UIImage image) {
  glBindVertexArray(vao);

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  GLenum format = image.num_channels == 3 ? GL_RGB : GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data.data());
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glUseProgram(image_shader_program);

  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(image_shader_program, "sTexture"), 0);

  glm::mat4 projection = glm::ortho(0.0f, (float)window->width, 0.0f, (float)window->height);
  glUniformMatrix4fv(glGetUniformLocation(image_shader_program, "uProjection"), 1, GL_FALSE,
                     glm::value_ptr(projection));

  // Set up the vertices for the image quad
  float xpos = image.position.x;
  float ypos = image.position.y;
  float w = image.size.x;
  float h = image.size.y;
  float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f},     {xpos + w, ypos, 1.0f, 1.0f},

                          {xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};

  glBindTexture(GL_TEXTURE_2D, texture_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Cleanup texture
  glDeleteTextures(1, &texture_id);
}

void UIManager::render(UILabel label) {
  // Activate corresponding render state
  glUseProgram(text_shader_program);
  glUniform3f(glGetUniformLocation(text_shader_program, "uTextColor"), label.color.r, label.color.g, label.color.b);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao);

  // Set up the projection matrix.
  glm::mat4 projection = glm::ortho(0.0f, (float)window->width, 0.0f, (float)window->height);
  glUniformMatrix4fv(glGetUniformLocation(text_shader_program, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

  // Iterate through all characters
  std::string::const_iterator c;
  for (c = label.text.begin(); c != label.text.end(); c++) {
    Character ch = characters[*c];

    float xpos = label.position.x + ch.bearing.x * label.scale;
    float ypos = label.position.y - (ch.size.y - ch.bearing.y) * label.scale;

    float w = ch.size.x * label.scale;
    float h = ch.size.y * label.scale;
    // Update VBO for each character
    float vertices[6][4] = {{xpos, ypos + h, 0.0, 0.0}, {xpos, ypos, 0.0, 1.0},     {xpos + w, ypos, 1.0, 1.0},

                            {xpos, ypos + h, 0.0, 0.0}, {xpos + w, ypos, 1.0, 1.0}, {xpos + w, ypos + h, 1.0, 0.0}};
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.texture_id);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    label.position.x += (ch.advance >> 6) * label.scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Cairn
