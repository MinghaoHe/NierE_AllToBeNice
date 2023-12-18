#version 410 core

layout (location = 0) in float life;
layout (location = 1) in float particle_size;
layout (location = 2) in vec3 velocity;
layout (location = 3) in vec3 color;

out vec4 particle_color;

uniform int duration;
uniform mat4 model;

void main() {
  vec3 translation = duration * velocity;
  if (length(translation) > life) {
    particle_color = vec4(0.0, 0.0, 0.0, 0.0);
  } else {
    particle_color = vec4(color, 1.0);
  }

  gl_PointSize = particle_size;
  gl_Position = model * vec4(0.0, 0.0, 0.0, 1.0) + vec4(translation, 0.0);
}
