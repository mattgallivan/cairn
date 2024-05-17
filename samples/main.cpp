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
    camera.left = 0.f;
    camera.right = width;
    camera.top = height;
    camera.bottom = 0.f;
  });

  // Build the mesh.
  Cairn::Mesh mesh;

  // Load and build the textures.
  Cairn::Resource resource_manager;

  Cairn::Texture* texture = resource_manager.load_texture("../resources/sprites/toast.png");
  Cairn::Texture* grass_texture = resource_manager.load_texture("../resources/sprites/grass.png");
  Cairn::Texture* sand_texture = resource_manager.load_texture("../resources/sprites/sand.png");
  Cairn::Texture* sand2_texture = resource_manager.load_texture("../resources/sprites/sand2.png");

  // Load the texture atlas.
  int width, height, channels;

  unsigned char* atlas_data = stbi_load("../resources/textures/blocks.png", &width, &height, &channels, 0);
  Cairn::TextureAtlas texture_atlas(atlas_data, width, height, channels, 48, 48);

  // Create the tilemap.
  std::vector<int> tilemap_data = {
      2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2,
      1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1,
      0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  };
  Cairn::Tilemap tilemap(10, 10, 48, 48, &texture_atlas, tilemap_data);

  Cairn::Tilemap tilemap2(10, 10, 48, 48, &texture_atlas, tilemap_data);
  tilemap2.position = glm::vec2(1000.f, 500.f);

  // Create the sprites.
  std::vector<Cairn::Sprite> sprites;
  Cairn::Sprite player_sprite(&mesh, texture);
  player_sprite.position = glm::vec2(400.f, 600.f);
  player_sprite.scale = glm::vec2(96.f, 96.f);
  player_sprite.rotation = 10.f;
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

  return 0;
}
