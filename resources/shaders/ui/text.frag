#version 410 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

uniform vec3 uTextColor;
uniform sampler2D sTexture;

void main() {
     vec4 sampled = vec4(1.0, 1.0, 1.0, texture(sTexture, inTexCoords).r);
     outColor = vec4(uTextColor, 1.0) * sampled;
}
