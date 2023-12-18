/****************************************************************************
**
** Copyright (C) 2024 MinghaoHe Private.
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

#include "render.h"

#include "atn/engine/render/define.h"

namespace atn::game::enemy {

RenderComponent::RenderComponent() {}

RenderComponent::~RenderComponent() {}

void RenderComponent::Tick(size_t delta) {
  if (pass_data_.empty()) {
    if (!seed_->logic.contains("text") || !seed_->logic.contains("scale")) {
      return;
    }
    const std::string text{seed_->logic["text"]};
    tag_ = std::string("enemy-") + text;
    std::shared_ptr<engine::render::TextPassData> text_pass_data{
        std::make_shared<engine::render::TextPassData>()};
    text_pass_data->text = text;
    text_pass_data->scale = seed_->logic["scale"].get<float>();
    text_pass_data->width = seed_->logic["width"].get<float>();
    text_pass_data->height = seed_->logic["height"].get<float>();
    pass_data_.push_back(text_pass_data);
  }

  for (auto data : pass_data_) {
    data->model = seed_->model;
  }
}

}  // namespace atn::game::enemy
