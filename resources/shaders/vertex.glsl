#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  gl_Position = projection * model * vec4(position, 1.0);
  TexCoords = tex_coords;
}
