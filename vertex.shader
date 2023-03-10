#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 modelMatrix;

void main() {
    gl_Position = modelMatrix * vec4(vertex, 1.0);
}
