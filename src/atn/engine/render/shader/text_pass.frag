#version 410 core

in vec2 texture_coords_fs;

out vec4 fragment_color;

uniform sampler2D character;
uniform vec3 text_color = vec3(1.0, 1.0, 1.0);

void main() {
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(character, texture_coords_fs).r);
  fragment_color = vec4(text_color, 0.8) * sampled;
}