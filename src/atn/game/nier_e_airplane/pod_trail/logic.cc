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

#include "logic.h"

#include <glm/gtc/matrix_transform.hpp>

#include "atn/utils/random.h"

namespace atn::game::pod_trail {

LogicComponent::LogicComponent(const glm::vec3 &force) : force_(force) {
  scale_ = glm::scale(glm::mat4{1.0f}, glm::vec3{utils::random::Float() / 10.0f + 0.9f});
}

LogicComponent::~LogicComponent() {}

void LogicComponent::Tick(size_t delta) {
  seed_->logic.clear();

  seed_->model =
      glm::translate(glm::mat4{1.0f}, force_ * speed_) * seed_->model *
      glm::rotate(glm::mat4{1.0f}, glm::radians(rotation_speed_ * delta), glm::vec3{1.0f}) * scale_;

  if (delta > life_) {
    seed_->existence = false;
  }
  life_ -= delta;
}

}  // namespace atn::game::pod_trail
