#version 410 core
out vec4 fragment_color;

in vec2 texture_coords_fs;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
  fragment_color = vec4(texture(texture0, texture_coords_fs).rgb + texture(texture1, texture_coords_fs).rgb, 1.0);
}
