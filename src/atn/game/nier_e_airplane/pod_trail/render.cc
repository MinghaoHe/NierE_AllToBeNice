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

#include "atn/engine/render/define.h"
#include "atn/game/nier_e_airplane/pod_trail/data.h"
#include "atn/utils/random.h"

namespace atn::game::pod_trail {

RenderComponent::RenderComponent() {
  std::shared_ptr<engine::render::NormalPassData> normal_pass_data{std::make_shared<engine::render::NormalPassData>()};
  normal_pass_data->vertices.assign(std::begin(data::cube_vertices), std::end(data::cube_vertices));
  tag_ = utils::random::UIntPtr() % 10 < 4 ? pod_trail::kCubeTag
                                           : pod_trail::kPrismTag;
  if (tag_.compare(kCubeTag) == 0) {
    normal_pass_data->indices.assign(std::begin(data::cube_indices), std::end(data::cube_indices));
    normal_pass_data->color = data::cube_color;
    normal_pass_data->draw_mode = GL_TRIANGLES;
  } else if (tag_.compare(kPrismTag) == 0) {
    normal_pass_data->indices.assign(std::begin(data::prism_indices), std::end(data::prism_indices));
    normal_pass_data->color = data::prism_color;
    normal_pass_data->draw_mode = GL_LINES;
  }

  pass_data_.push_back(normal_pass_data);
}

RenderComponent::~RenderComponent() {}

void RenderComponent::Tick(size_t delta) {
  for (auto data : pass_data_) {
    data->model = seed_->model;
  }
}

}  // namespace atn::game::pod_trail
