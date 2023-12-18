#version 410 core
out vec4 fragment_color;

in vec2 texture_coords_fs;

uniform sampler2D texture0;

uniform int x_blur;
uniform int y_blur;

uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);
uniform float x_weight[15] = float[] (0.1945945946, 0.1945945946, 0.1945945946,
                                      0.1216216216, 0.1216216216, 0.1216216216, 0.1216216216,
                                      0.0540540541, 0.0540540541, 0.0540540541, 0.0540540541, 0.054054054, 0.054054054,
                                      0.0162162162, 0.0162162162);
uniform float y_weight[18] = float[] (0.2270270270, 0.2270270270,
                                      0.1945945946, 0.1945945946,
                                      0.1216216216, 0.1216216216, 0.1216216216,
                                      0.0540540541, 0.0540540541, 0.0540540541, 0.0540540541, 0.0540540541, 0.0540540541,
                                      0.0162162162, 0.0162162162,  0.0162162162, 0.0162162162, 0.0162162162);

void main() {
  vec2 tex_offset = 1.0 / textureSize(texture0, 0);  // gets size of single texel
  vec3 color = texture(texture0, texture_coords_fs).rgb * weight[0];
  for (int i = 1; i < x_blur; ++i) {
    color += texture(texture0, texture_coords_fs + vec2(tex_offset.x * i, 0.0)).rgb * x_weight[i];
    color += texture(texture0, texture_coords_fs - vec2(tex_offset.x * i, 0.0)).rgb * x_weight[i];
  }
  for (int i = 0; i < y_blur; ++i) {
    color += texture(texture0, texture_coords_fs + vec2(0.0, tex_offset.y * i)).rgb * y_weight[i];
    color += texture(texture0, texture_coords_fs - vec2(0.0, tex_offset.y * i)).rgb * y_weight[i];
  }
  fragment_color = vec4(color, 1.0);
}
