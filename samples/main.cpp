#include "graphics.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "sprite.h"
#include "texture.h"
#include "window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

#include <functional>

int main() {
  // Create the window and graphics system.
  Cairn::Window window(800, 600, "Cairn Engine v0.1");
  Cairn::Graphics graphics(window);

  // Compile the shaders.
  const char* vertex_shader_source = "#version 330 core\n"
                                     "layout (location = 0) in vec3 position;\n"
                                     "layout (location = 1) in vec2 tex_coords;\n"
                                     "out vec2 TexCoords;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = projection * model * vec4(position, 1.0);\n"
                                     "   TexCoords = tex_coords;\n"
                                     "}\0";

  const char* fragment_shader_source = "#version 330 core\n"
                                       "in vec2 TexCoords;\n"
                                       "out vec4 color;\n"
                                       "uniform sampler2D tex;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   color = texture(tex, TexCoords);\n"
                                       "}\0";

  Cairn::Shader shader(vertex_shader_source, fragment_shader_source);
  if (!graphics.compile(shader)) {
    return 1;
  }

  // Create the camera.
  Cairn::Camera camera;
  window.add_resize_callback([&camera](int width, int height) {
    camera.projection = glm::ortho(0.f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.f, 1.f);
  });

  // Build the mesh.
  Cairn::Mesh mesh;
  graphics.build(mesh);

  // Load and build the texture.
  int width, height, channels;
  unsigned char* image_data = stbi_load("../resources/sprites/toast.png", &width, &height, &channels, 0);
  if (!image_data) {
    Cairn::Log::error(Cairn::Log::Category::Graphics, "Failed to load image data.");
    return 1;
  }

  Cairn::Texture texture(image_data, width, height, channels);
  graphics.build(texture);

  // Create the sprites.
  std::vector<Cairn::Sprite> sprites;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      Cairn::Sprite sprite(&mesh, &texture);
      sprite.position = glm::vec2(100.f + i * 30.f, 100.f + j * 30.f);
      sprite.scale = glm::vec2(96.f, 96.f);
      sprite.layer = (i + j) % 2 == 0 ? Cairn::SpriteLayer::Background : Cairn::SpriteLayer::Foreground;
      sprites.push_back(sprite);
    }
  }

  // Draw the sprite.
  while (window.is_open()) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    graphics.draw(shader, camera, sprites);

    window.refresh();
  }

  stbi_image_free(image_data);
  return 0;
}
