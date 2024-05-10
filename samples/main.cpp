#include "graphics.h"
#include "log.h"
#include "mesh.h"
#include "resource.h"
#include "shader.h"
#include "sprite.h"
#include "texture.h"
#include "tilemap.h"
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
  std::string vertex_shader_source = Cairn::Resource::load_shader("../resources/shaders/vertex.glsl");
  std::string fragment_shader_source = Cairn::Resource::load_shader("../resources/shaders/fragment.glsl");

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

  // Load and build the textures.
  int width, height, channels;
  unsigned char* image_data = stbi_load("../resources/sprites/toast.png", &width, &height, &channels, 0);
  if (!image_data) {
    Cairn::Log::error(Cairn::Log::Category::Graphics, "Failed to load image data.");
    return 1;
  }

  Cairn::Texture texture(image_data, width, height, channels);
  graphics.build(texture);

  unsigned char* grass_image_data = stbi_load("../resources/sprites/grass.png", &width, &height, &channels, 0);
  if (!grass_image_data) {
    Cairn::Log::error(Cairn::Log::Category::Graphics, "Failed to load image data.");
    return 1;
  }

  Cairn::Texture grass_texture(grass_image_data, width, height, channels);
  graphics.build(grass_texture);

  unsigned char* sand_image_data = stbi_load("../resources/sprites/sand.png", &width, &height, &channels, 0);
  if (!sand_image_data) {
    Cairn::Log::error(Cairn::Log::Category::Graphics, "Failed to load image data.");
    return 1;
  }

  Cairn::Texture sand_texture(sand_image_data, width, height, channels);
  graphics.build(sand_texture);

  unsigned char* sand2_image_data = stbi_load("../resources/sprites/sand2.png", &width, &height, &channels, 0);
  if (!sand2_image_data) {
    Cairn::Log::error(Cairn::Log::Category::Graphics, "Failed to load image data.");
    return 1;
  }

  Cairn::Texture sand2_texture(sand2_image_data, width, height, channels);
  graphics.build(sand2_texture);

  // Load the texture atlas.
  unsigned char* atlas_data = stbi_load("../resources/textures/spritesheet.png", &width, &height, &channels, 0);
  Cairn::TextureAtlas texture_atlas(atlas_data, width, height, channels, 96, 96);
  graphics.build(texture_atlas);

  // Create the tilemap.
  std::vector<int> tilemap_data = {
      2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2,
      1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1,
      0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  };
  Cairn::Tilemap tilemap(10, 10, 96, 96, &texture_atlas, tilemap_data);

  Cairn::Tilemap tilemap2(10, 10, 96, 96, &texture_atlas, tilemap_data);
  tilemap2.position = glm::vec2(1000.f, 500.f);

  // Create the sprites.
  std::vector<Cairn::Sprite> sprites;
  Cairn::Sprite player_sprite(&mesh, &texture);
  player_sprite.position = glm::vec2(240.f, 200.f);
  player_sprite.scale = glm::vec2(96.f, 96.f);
  sprites.push_back(player_sprite);

  // Draw the sprite.
  while (window.is_open()) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    graphics.draw(shader, camera, tilemap);
    graphics.draw(shader, camera, tilemap2);
    graphics.draw(shader, camera, sprites);

    window.refresh();
  }

  stbi_image_free(atlas_data);
  stbi_image_free(sand2_image_data);
  stbi_image_free(sand_image_data);
  stbi_image_free(grass_image_data);
  stbi_image_free(image_data);
  return 0;
}
