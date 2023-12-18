#version 410 core
out vec4 fragment_color;

in vec2 texture_coords_fs;

uniform sampler2D texture0;

void main() {
  fragment_color = texture(texture0, texture_coords_fs);
}
