#version 410 core

layout (location = 0) in vec4 vertex;
out vec2 texture_coords_fs;

uniform mat4 model_adjust_matrix;
uniform mat4 model;

void main() {
  gl_Position = model * vec4(vertex.xy, 0.0f, 1.0f);
  texture_coords_fs = vertex.zw;
}
