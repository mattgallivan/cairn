#version 410 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

uniform sampler2D sTexture;

void main() {
     outColor = texture(sTexture, inTexCoords);
}
