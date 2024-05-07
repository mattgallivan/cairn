#include "graphics.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
  // Create the window and graphics system.
  Cairn::Window window(800, 600, "Cairn Engine v0.1");
  Cairn::Graphics graphics(window);

  // Compile the shaders.
  const char* vertex_shader_source = "#version 330 core\n"
                                     "layout (location = 0) in vec3 position;\n"
                                     "uniform mat4 model;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = model * vec4(position, 1.0);\n"
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

  // Create the sprites.
  const glm::mat4 transform1 =
      glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), glm::vec3(0.5f, 0.5f, 0.0f));
  Cairn::Sprite sprite1(mesh, transform1);

  const glm::mat4 transform2 =
      glm::rotate(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), glm::vec3(-0.5f, -0.5f, 0.0f)),
                  glm::radians(145.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  Cairn::Sprite sprite2(mesh, transform2);

  // Draw the sprite.
  while (window.is_open()) {
    graphics.draw(shader, sprite1);
    graphics.draw(shader, sprite2);
    window.refresh();
  }
  return 0;
}
