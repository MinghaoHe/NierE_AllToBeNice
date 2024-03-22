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

#include <numbers>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "atn/game/nier_e_airplane/pod_bullet.h"
#include "atn/game/nier_e_airplane/pod_bullet/data.h"
#include "atn/game/nier_e_airplane/pod_trail.h"
#include "atn/utils/random.h"

namespace {

bool Cooldown(size_t& delta, const size_t cooldown, const size_t tick_delta) {
  delta += tick_delta;
  if (delta < cooldown) {
    return true;
  }
  delta = 0;
  return false;
}

}

namespace atn::game::pod {

LogicComponent::LogicComponent() {}

LogicComponent::~LogicComponent() {}

void LogicComponent::Tick(size_t delta) {
  seed_->logic.clear();

  Transform(delta);
  if (IsMoving()) {
    Trail(delta);
  }
  if (key_input_.contains(SDLK_SPACE)) {
    Shoot(delta);
  }
}

void LogicComponent::Transform(size_t delta) {
  Rotate();
  if (IsMoving()) {
    Translate(speed_ * delta);
  }
  seed_->model = translation_ * rotation_;
}

void LogicComponent::Trail(size_t delta) {
  if (Cooldown(trace_delta_, trace_cooldown_, delta)) return;

  for (size_t i{0}; i < utils::random::UIntPtr() % 5 + 1; ++i) {
    std::shared_ptr<pod_trail::EntityCreateParam> create_param{std::make_shared<pod_trail::EntityCreateParam>()};
    create_param->model = TracePosTrans() * seed_->model;
    create_param->force = -1.0f * force_;
    CreateEntity(create_param);

    trace_cooldown_ = utils::random::UIntPtr() % 50 + 75;
  }
}

void LogicComponent::Shoot(size_t delta) {
  if (Cooldown(shoot_delta_, shoot_cooldown_, delta)) return;
  seed_->logic["audio"] = "shoot";

  std::shared_ptr<pod_bullet::EntityCreateParam> create_param{std::make_shared<pod_bullet::EntityCreateParam>()};
  create_param->model = BulletPosTrans() * seed_->model;
  CreateEntity(create_param);
}

void LogicComponent::Translate(float length) {
  force_ = {};
  if (key_input_.contains(SDLK_w)) {
    force_.y += length;
  }
  if (key_input_.contains(SDLK_a)) {
    force_.x -= length;
  }
  if (key_input_.contains(SDLK_s)) {
    force_.y -= length;
  }
  if (key_input_.contains(SDLK_d)) {
    force_.x += length;
  }
  translation_ = glm::translate(translation_, force_);
  translation_[3][0] = std::clamp(translation_[3][0], -1.0f, 1.0f);
  translation_[3][1] = std::clamp(translation_[3][1], -1.0f, 1.0f);
}

void LogicComponent::Rotate() {
  auto [x, y] = mouse_pos_;
  glm::vec4 pod_pos{translation_ * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
  x -= pod_pos.x;
  y -= pod_pos.y;
  glm::mat4 rotation{1.0f};
  rotation_ = glm::rotate(rotation, std::atan2(y, x) - std::numbers::pi_v<float> / 2.0f,
                  glm::vec3{0.0f, 0.0f, 1.0f});
}

bool LogicComponent::IsMoving() const {
  return key_input_.contains(SDLK_w) || key_input_.contains(SDLK_a) ||
         key_input_.contains(SDLK_s) || key_input_.contains(SDLK_d);
}

glm::mat4 LogicComponent::BulletPosTrans() const {
  glm::vec3 translate{rotation_ * glm::vec4{0.0f, pod_bullet::data::height / 2.0f + 0.08, 0.0f, 1.0}};
  return glm::translate(glm::mat4(1.0f), translate);
}

glm::mat4 LogicComponent::TracePosTrans() const {
  glm::vec3 move{rotation_ * glm::vec4{0.0f, -0.04f + utils::random::Float() * 0.02f, 0.0f, 1.0}};
  glm::mat4 trans{glm::translate(glm::mat4{1.0f}, move)};
  glm::vec3 cross{glm::normalize(glm::cross(move, glm::vec3{0.0f, 0.0f, 1.0f}))};
  trans = glm::translate(trans, cross * utils::random::Float() * 0.04f);
  return trans;
}

}  // namespace atn::game::pod
