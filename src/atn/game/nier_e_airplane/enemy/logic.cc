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

#include "logic.h"

#include <glm/gtc/matrix_transform.hpp>

#include "atn/engine/render/text.h"
#include "atn/engine/physics/define.h"
#include "atn/game/nier_e_airplane/explosion.h"
#include "atn/utils/random.h"

#ifdef max
#undef max
#endif  // max

extern std::weak_ptr<atn::engine::render::Text> gtext_render;

namespace {

bool Cooldown(size_t &delta, const size_t cooldown, const size_t tick_delta) {
  delta += tick_delta;
  if (delta < cooldown) {
    return true;
  }
  delta = 0;
  return false;
}

}


namespace atn::game::enemy {

LogicComponent::LogicComponent(const LogicCreateParam &create_param) {
  text_ = create_param.text;
  scale_ = create_param.scale;
  for (char c : text_) {
    const engine::render::Character &character = gtext_render.lock()->CharFont(c);
    height_ = std::max(height_, static_cast<float>(character.size.y)) * scale_;
    width_ += (character.advance >> 6) * scale_;
  }
  track_.SetEnemyTrace(create_param.track_class);
}

LogicComponent::~LogicComponent() {}

void LogicComponent::Tick(size_t delta) {
  collision_ = seed_->logic.contains("collision") && !seed_->logic["collision"].get<std::string>().empty();

  seed_->logic.clear();

  seed_->logic["text"] = text_;
  seed_->logic["scale"] = scale_;
  seed_->logic["width"] = width_;
  seed_->logic["height"] = height_;
  seed_->logic["box_class"] = engine::physics::BoxClass::Rectangle;


  if (collision_) {
    shake_delta_ = data::shake_cooldown;
    seed_->logic["audio"] = "hit";
    --life_;
    UnderAttack(delta);
  }

  if (shake_delta_ > delta) {
    shake_delta_ -= delta;
    seed_->model = glm::translate(seed_->model, glm::vec3(utils::random::Float() / 150.0f,
                                                          utils::random::Float() / 150.0f, 0.0f));
  } else {
    seed_->model = track_.TrackModel(delta, seed_->model);
  }
  Shoot(delta);

  if (life_ < 0) {
    Seed()->existence = false;
    Seed()->game_block->destory_count.fetch_add(1);
  }
}

void LogicComponent::Shoot(size_t delta) {
  if (Cooldown(shoot_delta_, shoot_cooldown_, delta)) return;
  for (auto create_param : shoot_.Attack(logic::ShootClass::Normal, seed_->model)) {
    CreateEntity(create_param);
  }
}

void LogicComponent::UnderAttack(size_t delta) {
  std::shared_ptr<explosion::EntityCreateParam> create_param{std::make_shared<explosion::EntityCreateParam>()};
  create_param->type = life_ > 2 ? explosion::Type::kHit : explosion::Type::kDestroy;
  create_param->model = seed_->model;
  CreateEntity(create_param);
}

}  // namespace atn::game::enemy
