#include "graphics.h"
#include "input.h"
#include "log.h"
#include "mesh.h"
#include "resource.h"
#include "shader.h"
#include "sprite.h"
#include "texture.h"
#include "tilemap.h"
#include "ui.h"
#include "window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

int main() {
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;

  // Create the window and graphics system.
  Cairn::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Cairn Engine v0.3.0");
  Cairn::Graphics graphics(window);

  // Register the input with the window.
  Cairn::InputManager input_manager;
  Cairn::InputProfile profile;
  profile.map(Cairn::KeyboardEvent(Cairn::KeyboardEvent::Key::Escape, Cairn::InputEvent::State::Press),
              [&window](const Cairn::InputEvent& event) { window.close(); });
  profile.map(Cairn::MousePositionEvent(), [](const Cairn::InputEvent& event) {
    const Cairn::MousePositionEvent& mouse_event = static_cast<const Cairn::MousePositionEvent&>(event);
  });
  input_manager.add(&profile);
  window.bind(&input_manager);

  // Create the user interface.
  Cairn::UIManager ui_manager(&window);

  // Create UI elements using std::make_unique.
  std::vector<std::unique_ptr<Cairn::UIElement>> ui_elements;
  ui_elements.push_back(
      std::make_unique<Cairn::UILabel>("BEAN BANDANA", glm::vec2(400.f, 700.f), glm::vec2(100.f, 100.f), Cairn::White));
  ui_elements.push_back(
      std::make_unique<Cairn::UILabel>("Introducing...", glm::vec2(400.f, 750.f), glm::vec2(100.f, 100.f), Cairn::Red));

  std::string file_path = "../resources/textures/portrait.png";
  int xwidth, xheight, xchannels;
  unsigned char* image_data = stbi_load(file_path.c_str(), &xwidth, &xheight, &xchannels, 0);
  if (image_data) {
    std::vector<unsigned char> image_data_vector(image_data, image_data + xwidth * xheight * xchannels);
    ui_elements.push_back(std::make_unique<Cairn::UIImage>(glm::vec2(1000.f, 1000.f), glm::vec2(100.f, 100.f),
                                                           image_data_vector, xwidth, xheight, xchannels));
    stbi_image_free(image_data); // Free the image data after creating the UIImage.
  } else {
    std::cerr << "Failed to load image: " << file_path << std::endl;
    return 1;
  }

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
  stbi_image_free(atlas_data); // Free the image data after creating the TextureAtlas.

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
  std::vector<Cairn::Sprite*> sprites;
  Cairn::Sprite player_sprite(&mesh, texture);
  player_sprite.position = glm::vec2(400.f, 600.f);
  player_sprite.scale = glm::vec2(96.f, 96.f);
  player_sprite.rotation = 10.f;
  sprites.push_back(&player_sprite);

  profile.map(Cairn::MouseButtonEvent(Cairn::MouseButtonEvent::MouseButton::Left, Cairn::InputEvent::State::Press),
              [&player_sprite](const Cairn::InputEvent& event) {
                const Cairn::MouseButtonEvent& mouse_event = static_cast<const Cairn::MouseButtonEvent&>(event);
                player_sprite.position = glm::vec2(mouse_event.x, mouse_event.y);
              });

  // Draw the sprite.
  while (window.is_open()) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    graphics.draw(shader, camera, tilemap);
    graphics.draw(shader, camera, tilemap2);
    graphics.draw(shader, camera, sprites);

    ui_manager.render(ui_elements);

    window.refresh();
  }

  return 0;
}
