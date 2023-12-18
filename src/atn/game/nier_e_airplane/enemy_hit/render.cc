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

#include "render.h"

#include <glm/gtc/matrix_transform.hpp>

#include "atn/engine/render/define.h"
#include "atn/game/nier_e_airplane/enemy_hit/data.h"
#include "atn/utils/random.h"

namespace atn::game::enemy_hit {

RenderComponent::RenderComponent() {
  std::shared_ptr<engine::render::FadePassData> fade_pass_data{std::make_shared<engine::render::FadePassData>()};

  float random = utils::random::Float();
  if (random > 0.5f) {
    fade_pass_data->vertices.assign(std::begin(data::vertices1), std::end(data::vertices1));
    fade_pass_data->indices.assign(std::begin(data::indices1), std::end(data::indices1));
    tag_ = "enemy_hit_1";
  } else if (random > 0.0f) {
    fade_pass_data->vertices.assign(std::begin(data::vertices2), std::end(data::vertices2));
    fade_pass_data->indices.assign(std::begin(data::indices2), std::end(data::indices2));
    tag_ = "enemy_hit_2";
  } else {
    fade_pass_data->vertices.assign(std::begin(data::vertices3), std::end(data::vertices3));
    fade_pass_data->indices.assign(std::begin(data::indices3), std::end(data::indices3));
    tag_ = "enemy_hit_3";
  }

  if (random < -0.5f) {
    rotation_ = glm::rotate(glm::mat4{1.0f}, glm::radians(-45.0f), glm::vec3{1.0f});
  }

  fade_pass_data->color = data::color;
  fade_pass_data->fade_rate = data::fade_rate;
  pass_data_.push_back(fade_pass_data);
}

RenderComponent::~RenderComponent() {}

void RenderComponent::Tick(size_t delta) {
  for (auto data : pass_data_) {
    data->model = seed_->model * rotation_;
  }
}

}  // namespace atn::game::pod_bullet
