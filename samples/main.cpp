#include "graphics.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "window.h"

int main() {
  // Create the window and graphics system.
  Cairn::Window window(800, 600, "Cairn Engine v0.1");
  Cairn::Graphics graphics(window);

  // Compile the shaders.
  const char* vertex_shader_source = "#version 330 core\n"
                                     "layout (location = 0) in vec3 position;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(position, 1.0);\n"
                                     "}\0";

  const char* fragment_shader_source = "#version 330 core\n"
                                       "out vec4 color;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   color = vec4(1.0, 0.5, 0.2, 1.0);\n"
                                       "}\0";

  Cairn::Shader shader(vertex_shader_source, fragment_shader_source);
  if (!graphics.compile(shader)) {
    return 1;
  }

  // Build the mesh.
  Cairn::Mesh mesh;
  graphics.build(mesh);

  // Create the sprite.
  Cairn::Sprite sprite(mesh);

  // Draw the sprite.
  while (window.is_open()) {
    graphics.draw(shader, sprite);
    window.refresh();
  }
  return 0;
}
