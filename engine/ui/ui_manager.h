#pragma once

#include "shader.h"
#include "ui_image.h"
#include "ui_label.h"
#include "ui_element.h"
#include "window.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

namespace Cairn {

struct Character {
    unsigned int texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class UIManager {
public:
    UIManager(Window* window);

    ~UIManager();

    void render(const std::vector<std::unique_ptr<UIElement>>& elements);

private:
    GLuint compile_shader(GLenum type, const char* source);

    GLuint create_shader_program(Shader* shader);

    void renderImage(const UIImage& image);

    void renderText(const UILabel& label);

    std::unordered_map<GLchar, Character> characters;

    GLuint vao, vbo;

    GLuint image_shader_program, text_shader_program;

    std::unique_ptr<Shader> image_shader;
    std::unique_ptr<Shader> text_shader;

    Window* window;
};

} // namespace Cairn
