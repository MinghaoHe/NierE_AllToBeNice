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

#include "text.h"

#include <ranges>

#include "atn/engine/render/text.h"

#ifdef max
#undef max
#endif  // max

extern std::weak_ptr<atn::engine::render::Text> gtext_render;

namespace atn::engine::render {

TextPass::TextPass(std::shared_ptr<Framebuffer> main_frame)
    : Pass(main_frame),
      text_shader_("res/shader/text_pass.vert",
                   "res/shader/text_pass.frag") {}

TextPass::~TextPass() { DelAllTextRdrObjs(); }

void TextPass::PrevDraw(size_t delta) {}

void TextPass::Draw(const std::string &tag, std::shared_ptr<PassData> pass_data,
                    size_t delta) {
  std::shared_ptr<TextPassData> text_pass_data{std::static_pointer_cast<render::TextPassData>(pass_data)};
  const std::string &text{text_pass_data->text};
  if (!rdr_objs_.contains(tag)) {
    rdr_objs_.insert(std::make_pair(tag, GenTextRdrObjs(text, text_pass_data->scale,
                                           text_pass_data->width, text_pass_data->height)));
  }
  main_frame_->Bind();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  EnableShader(text_pass_data->model);
  glActiveTexture(GL_TEXTURE0);
  for (size_t i{0}; i < text.size(); ++i) {
    glBindVertexArray(rdr_objs_[tag][i].vao);
    glBindTexture(GL_TEXTURE_2D, gtext_render.lock()->CharFont(text[i]).texture);
    glDrawElements(text_pass_data->draw_mode, rdr_objs_[tag][i].ebo_count, GL_UNSIGNED_INT, 0);
  }

  glDisable(GL_BLEND);
  main_frame_->Unbind();
}

GLuint TextPass::PostDraw(size_t delta) { return 0; }

std::vector<RdrObj> TextPass::GenTextRdrObjs(const std::string &text, float scale, float width, float height) {
  std::vector<RdrObj> rdr_objs;
  GLfloat x = -width / 2.0f;
  GLfloat y = -height / 2.0f;
  for (char c : text) {
    const Character &char_texture = gtext_render.lock()->CharFont(c);
    GLfloat xpos = x + char_texture.bearing.x * scale;

    GLfloat w = char_texture.size.x * scale;
    GLfloat hh = y + char_texture.bearing.y * scale;
    GLfloat hl = y + (char_texture.bearing.y - char_texture.size.y) * scale;

    GLfloat vertices[]{
            xpos,     0.0f + hh, 0.0f, 0.0f,
            xpos,     0.0f + hl, 0.0f, 1.0f,
            xpos + w, 0.0f + hl, 1.0f, 1.0f,
            xpos + w, 0.0f + hh, 1.0f, 0.0f};
    GLuint indices[]{0, 1, 2, 0, 2, 3};

    rdr_objs.push_back(GenRdrObject(vertices, indices));
    SetAttribPointer({{4, 4, 0}});

    x += (char_texture.advance >> 6) * scale;
  }
  return rdr_objs;
}

void TextPass::DelAllTextRdrObjs() {
  for (auto &rdr_objs : rdr_objs_ | std::views::values) {
    for (auto &rdr_obj : rdr_objs) {
      DelRdrObject(rdr_obj);
    }
  }
  rdr_objs_.clear();
}

void TextPass::EnableShader(const glm::mat4 &model) {
  text_shader_.Use();
  text_shader_.SetInt("character", 0);
  text_shader_.SetMatrix4("model", model);
}

}  // namespace atn::engine::render
