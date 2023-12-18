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

#include "normal.h"

#include "atn/engine/render/object.h"

namespace atn::engine::render {

NormalPass::NormalPass(std::shared_ptr<Framebuffer> main_frame)
    : Pass(main_frame)
    , shader_("res/shader/normal_pass.vert", "res/shader/normal_pass.frag") {}

NormalPass::~NormalPass() {}

void NormalPass::PrevDraw(size_t delta) {
  if (rdr_objs_.empty()) return;
}

void NormalPass::Draw(const std::string &tag,
                      std::shared_ptr<PassData> pass_data, size_t delta) {
  std::shared_ptr<NormalPassData> normal_pass_data{std::static_pointer_cast<render::NormalPassData>(pass_data)};

  main_frame_->Bind();
  if (!rdr_objs_.contains(tag)) {
    rdr_objs_.insert(std::make_pair(tag, GenRdrObject(normal_pass_data->vertices, normal_pass_data->indices)));
    SetAttribPointer({{3, 3, 0}});
  } else {
    glBindVertexArray(rdr_objs_[tag].vao);
  }
  EnableShader(normal_pass_data->model, normal_pass_data->color);
  glDrawElements(normal_pass_data->draw_mode, rdr_objs_[tag].ebo_count, GL_UNSIGNED_INT, 0);
  main_frame_->Unbind();
}

GLuint NormalPass::PostDraw(size_t delta) {
  return 0;
}

void NormalPass::EnableShader(const glm::mat4 &model, const glm::vec3 &color) {
  shader_.Use();

  shader_.SetMatrix4("model", model);
  shader_.SetVec3("color", color);
}

}  // namespace atn::engine::render
