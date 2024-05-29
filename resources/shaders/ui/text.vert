#version 410 core

layout(location = 0) in vec4 aVertex;

layout(location = 0) out vec2 outTexCoords;

uniform mat4 uProjection;

void main() {
     gl_Position = uProjection * vec4(aVertex.xy, 0.0, 1.0);
     outTexCoords = aVertex.zw;
}
