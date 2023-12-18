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

#include "shoot.h"

#include <numbers>

#include "atn/game/nier_e_airplane/enemy_bullet/data.h"
#include "atn/utils/random.h"

namespace atn::game::enemy::logic {

Shoot::Shoot() {}

Shoot::~Shoot() {}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::Attack(
    ShootClass shoot_class, const glm::mat4 &model) const {
  switch (shoot_class) {
    case ShootClass::Normal: {
      return NormalAttack(model);
    } break;
    case ShootClass::Medium: {
      return MediumAttack(model);
    } break;
    case ShootClass::Hard: {
      return HardAttack(model);
    } break;
    case ShootClass::Hell: {
      return HellAttack(model);
    } break;
    case ShootClass::Sp3: {
      return Sp3Attack(model);
    } break;
    case ShootClass::Sp4: {
      return Sp4Attack(model);
    } break;
    case ShootClass::Sp6: {
      return Sp6Attack(model);
    } break;
  }
  return {};
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::NormalAttack(
    const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  float radians = utils::random::Float() * std::numbers::pi_v<float>;
  glm::mat4 rotation {
      {std::cos(radians),  std::sin(radians), 0.0f, 0.0f},
      {std::sin(radians), -std::cos(radians), 0.0f, 0.0f},
      {0.0f, 0.0f, 1.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f}};

  std::shared_ptr<enemy_bullet::EntityCreateParam> create_param{std::make_shared<enemy_bullet::EntityCreateParam>()};
  create_param->model = model * rotation;
  if (utils::random::Float() > 0.4f) {
    create_param->color = enemy_bullet::data::red;
    create_param->collision = false;
  } else {
    create_param->color = enemy_bullet::data::orange;
    create_param->collision = true;
  }
  create_list.push_back(create_param);
  return create_list;
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::MediumAttack(
        const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  return create_list;
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::HardAttack(
        const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  return create_list;
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::HellAttack(
        const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  return create_list;
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::Sp3Attack(
        const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  return create_list;
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::Sp4Attack(
        const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  return create_list;
}

std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Shoot::Sp6Attack(
        const glm::mat4 &model) const {
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> create_list;
  return create_list;
}

}  // namespace atn::game::enemy::logic
