#version 330 core

layout (location = 0) in vec3 vertex;

uniform vec3 position;

void main() {
    gl_Position = vec4(vertex + position, 1.0);
}
