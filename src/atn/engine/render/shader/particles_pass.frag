#version 410 core
out vec4 fragment_color;
in vec4 particle_color;

void main() {
  fragment_color = particle_color;
}
