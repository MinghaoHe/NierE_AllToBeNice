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

#include "canvas_frame.h"

namespace atn::engine::render {

const GLfloat vertices[] {
        // positions  // tex_coords
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f};
const GLuint indices[] {0, 1, 2,
                        0, 2, 3};

CanvasFrame::CanvasFrame()
    : canvas_shader_("res/shader/canvas.vert",
                     "res/shader/canvas.frag"),
      canvas_mixer_shader_("res/shader/canvas_mixer.vert",
                           "res/shader/canvas_mixer.frag") {
  canvas_objs_ = GenRdrObject(vertices, indices);
  SetAttribPointer({{2, 4, 0}, {2, 4, 2}});
}

CanvasFrame::~CanvasFrame() { DelRdrObject(canvas_objs_); }

void CanvasFrame::Draw(const std::vector<GLuint> &textures) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindVertexArray(canvas_objs_.vao);

  Shader *shader = textures.size() > 1 ? &canvas_mixer_shader_ : &canvas_shader_;
  shader->Use();

  for (size_t i = 0; i < textures.size(); ++i) {
    std::string name{std::string("texture") + std::to_string(i)};
    shader->SetInt(name, i);
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, textures[i]);
  }
  glDrawElements(GL_TRIANGLES, canvas_objs_.ebo_count, GL_UNSIGNED_INT, 0);
}

void CanvasFrame::Clear() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

}  // namespace atn::engine::render
