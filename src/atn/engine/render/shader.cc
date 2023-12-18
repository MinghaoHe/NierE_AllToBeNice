/****************************************************************************
**
** Copyright (C) 2023 MinghaoHe Private.
**
** This file is part of the NierE_AllToBeNice, which is the shoot game for ending 'E' in Nier.
**
** Licensed under the MIT license.
** A copy of the MIT License is included in this file.
**
**
** $BEGIN_LICENSE:MIT$
**
** Terms of the MIT License:
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
** rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions of
** the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
** LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
** NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
** WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** $END_LICENSE$
**
****************************************************************************/

#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

namespace atn::engine::render {

Shader::Shader(const std::filesystem::path &vertex_shader_path,
               const std::filesystem::path &fragment_shader_path)
    : vertex_shader_path_(vertex_shader_path),
      fragment_shader_path_(fragment_shader_path) {}

Shader::~Shader() { Delete(); }

void Shader::Use() { 
  if (shader_program_id_ == 0) {
    Build();
  }
  glUseProgram(shader_program_id_);
}

void Shader::SetInt(const std::string_view name, int i) const {
  glUniform1i(glGetUniformLocation(shader_program_id_, name.data()), i);
}

void Shader::SetBoolean(const std::string_view name, bool b) const {
  glUniform1i(glGetUniformLocation(shader_program_id_, name.data()), b ? 1 : 0);
}

void Shader::SetFloat(const std::string_view name, float value) const {
  glUniform1f(glGetUniformLocation(shader_program_id_, name.data()), value);
}

void Shader::SetVec3(const std::string_view name,
                     const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(shader_program_id_, name.data()), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string_view name, float x, float y,
                     float z) const {
  glUniform3f(glGetUniformLocation(shader_program_id_, name.data()), x, y, z);
}

void Shader::SetMatrix4(const std::string_view name,
                        const glm::mat4 &matrix) const {
  glUniformMatrix4fv(glGetUniformLocation(shader_program_id_, name.data()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Build() {
  std::ifstream vertex_shader_file(vertex_shader_path_);
  std::stringstream vertex_shader_stream;
  vertex_shader_stream << vertex_shader_file.rdbuf();
  std::string vertex_shader_source{vertex_shader_stream.str()};

  std::ifstream fragment_shader_file(fragment_shader_path_);
  std::stringstream fragment_shader_stream;
  fragment_shader_stream << fragment_shader_file.rdbuf();
  std::string fragment_shader_source{fragment_shader_stream.str()};

  Build(vertex_shader_source, fragment_shader_source);
}

void Shader::Build(const std::string_view vertex_shader_source,
                   const std::string_view fragment_shader_source) {
  GLuint vertex_shader{glCreateShader(GL_VERTEX_SHADER)};
  const GLchar *vertex_shader_source_list[]{vertex_shader_source.data()};
  glShaderSource(vertex_shader, 1, vertex_shader_source_list, nullptr);
  glCompileShader(vertex_shader);
  CheckCompileError(vertex_shader);

  GLuint fragment_shader{glCreateShader(GL_FRAGMENT_SHADER)};
  const GLchar *fragment_shader_source_list[]{fragment_shader_source.data()};
  glShaderSource(fragment_shader, 1, fragment_shader_source_list, nullptr);
  glCompileShader(fragment_shader);
  CheckCompileError(fragment_shader);

  shader_program_id_ = glCreateProgram();
  glAttachShader(shader_program_id_, vertex_shader);
  glAttachShader(shader_program_id_, fragment_shader);
  glLinkProgram(shader_program_id_);
  CheckLinkError(shader_program_id_);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::Delete() {
  if (shader_program_id_ == 0) {
    return;
  }
  glDeleteProgram(shader_program_id_);
}

void Shader::CheckCompileError(GLuint shader) {
  GLint compile_result{0};
  GLchar error_message[1024]{};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
  if (!compile_result) {
    glGetShaderInfoLog(shader, sizeof(error_message), nullptr, error_message);
    std::cerr << "shader compile fail, message: " << error_message << std::endl;
  }
}

void Shader::CheckLinkError(GLuint program) {
  GLint link_result{0};
  GLchar error_message[1024]{};
  glGetProgramiv(program, GL_LINK_STATUS, &link_result);
  if (!link_result) {
    glGetProgramInfoLog(program, sizeof(error_message), nullptr, error_message);
    std::cerr << "shader link fail, message: " << error_message << std::endl;
  }
}

}  // namespace atn::engine::render
