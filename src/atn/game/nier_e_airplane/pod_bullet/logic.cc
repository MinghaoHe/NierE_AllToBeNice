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

#include "atn/engine/physics/define.h"
#include "atn/game/nier_e_airplane/enemy_hit.h"

namespace atn::game::pod_bullet {

LogicComponent::LogicComponent() {}

LogicComponent::~LogicComponent() {}

void LogicComponent::Tick(size_t delta) {
  bool collision = seed_->logic.contains("collision");
  std::string collider = collision ? seed_->logic["collision"].get<std::string>() : "";

  seed_->logic.clear();

  seed_->logic["box_class"] = engine::physics::BoxClass::Rectangle;
  seed_->logic["width"] = data::width;
  seed_->logic["height"] = data::height;

  glm::mat4 trans{glm::translate(glm::mat4{1.0f}, glm::vec3{0, speed_ * delta, 0})};
  seed_->model = seed_->model * trans;
  if (collision && collider.compare(kEnemyTag) == 0) {
    auto enemy_hit = std::make_shared<game::enemy_hit::EntityCreateParam>();
    glm::vec3 hit_trans = seed_->model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    enemy_hit->model = glm::translate(glm::mat4{1.0f}, hit_trans);
    CreateEntity(enemy_hit);
  }

  glm::vec4 position{seed_->model * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
  if (collision || position.x > 1.0f || position.x < -1.0f ||
      position.y > 1.0f || position.y < -1.0f) {
    seed_->existence = false;
  }
}

}  // namespace atn::game::pod_bullet
