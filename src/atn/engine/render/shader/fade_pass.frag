#version 410 core
out vec4 fragment_color;

uniform vec3 color;
uniform float fade;

void main() {
  fragment_color = vec4(color, 1.0 - fade);
}
