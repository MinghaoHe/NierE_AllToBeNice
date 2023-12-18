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

#include "bloom.h"

#include "atn/engine/render/object.h"

namespace atn::engine::render {

static const GLfloat vertices[]{
    // positions  // tex_coords
    -1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f};
static const GLuint indices[]{0, 1, 2, 0, 2, 3};

BloomPass::BloomPass(std::shared_ptr<Framebuffer> main_frame)
    : Pass(main_frame),
      normal_shader_("res/shader/normal_pass.vert",
                     "res/shader/normal_pass.frag"),
      bloom_shader_("res/shader/bloom_pass.vert",
                    "res/shader/bloom_pass.frag") {
  blur_src_fb_ = std::make_unique<Framebuffer>(main_frame_->width, main_frame_->height);
  blur_dst_fb_ = std::make_unique<Framebuffer>(main_frame_->width, main_frame_->height);

  bloom_objs_ = GenRdrObject(vertices, indices);
  SetAttribPointer({{2, 4, 0}, {2, 4 , 2}});
}

BloomPass::~BloomPass() { DelRdrObject(bloom_objs_); }

void BloomPass::PrevDraw(size_t delta) {
  if (rdr_objs_.empty()) return;
  blur_src_fb_->Clear();
  blur_dst_fb_->Clear();

  is_passing = false;
}

void BloomPass::Draw(const std::string &tag,
                     std::shared_ptr<PassData> pass_data, size_t delta) {
  std::shared_ptr<BloomPassData> bloom_pass_data{std::static_pointer_cast<render::BloomPassData>(pass_data)};

  blur_src_fb_->Bind();
  if (!rdr_objs_.contains(tag)) {
    rdr_objs_.insert(std::make_pair(tag, GenRdrObject(bloom_pass_data->vertices, bloom_pass_data->indices)));
    SetAttribPointer({{3, 3, 0}});
  } else {
    glBindVertexArray(rdr_objs_[tag].vao);
  }
  EnableNormalShader(bloom_pass_data->model, bloom_pass_data->bloom_color);
  glDrawElements(bloom_pass_data->draw_mode, rdr_objs_[tag].ebo_count, GL_UNSIGNED_INT, 0);
  blur_src_fb_->Unbind();

  is_passing = true;
}

GLuint BloomPass::PostDraw(size_t delta) {
  if (rdr_objs_.empty() || !is_passing) return 0;

  BlurPass();
  return blur_dst_fb_->Texture();
}

void BloomPass::BlurPass() {
  blur_dst_fb_->Bind();
  glBindVertexArray(bloom_objs_.vao);
  EnableBlurShader(15, 18);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, blur_src_fb_->Texture());
  glDrawElements(GL_TRIANGLES, bloom_objs_.ebo_count, GL_UNSIGNED_INT, 0);
  blur_dst_fb_->Unbind();
}

void BloomPass::EnableNormalShader(const glm::mat4 &model, const glm::vec3 &color) {
  normal_shader_.Use();

  normal_shader_.SetMatrix4("model", model);
  normal_shader_.SetVec3("color", color);
}

void BloomPass::EnableBlurShader(int x_blur, int y_blur) {
  bloom_shader_.Use();
  bloom_shader_.SetInt("texture0", 0);
  bloom_shader_.SetInt("x_blur", x_blur);
  bloom_shader_.SetInt("y_blur", y_blur);
}

}  // namespace atn::engine::render
