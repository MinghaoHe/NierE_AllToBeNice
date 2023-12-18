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

#include <numbers>

namespace atn::game::enemy_bullet {

RenderComponent::RenderComponent(const RenderCreateParam &create_param) {
  color_ = create_param.color;
}

RenderComponent::~RenderComponent() {}

void RenderComponent::Tick(size_t delta) {
  if (pass_data_.empty()) {
    if (!seed_->logic.contains("radius")) return;
    const GLuint N{48};
    float radius{seed_->logic["radius"].get<float>()};
    std::shared_ptr<engine::render::NormalPassData> normal_pass_data{
        std::make_shared<engine::render::NormalPassData>()};

    normal_pass_data->vertices.push_back(0.0f);
    normal_pass_data->vertices.push_back(0.0f);
    normal_pass_data->vertices.push_back(-0.1f);
    for (GLuint i{0}; i < N; ++i) {
      normal_pass_data->vertices.push_back(radius * std::cos(2.0f * std::numbers::pi_v<float> / N * i));
      normal_pass_data->vertices.push_back(radius * std::sin(2.0f * std::numbers::pi_v<float> / N * i));
      normal_pass_data->vertices.push_back(-0.1f);
    }
    for (GLuint i{1}; i < N; ++i) {
      normal_pass_data->indices.push_back(0);
      normal_pass_data->indices.push_back(i);
      normal_pass_data->indices.push_back(i + 1);
    }
    normal_pass_data->indices.push_back(0);
    normal_pass_data->indices.push_back(1);
    normal_pass_data->indices.push_back(N);

    normal_pass_data->color = color_;

    pass_data_.push_back(normal_pass_data);
  }

  for (auto data : pass_data_) {
    data->model = seed_->model;
  }
}

}  // namespace atn::game::enemy_bullet
