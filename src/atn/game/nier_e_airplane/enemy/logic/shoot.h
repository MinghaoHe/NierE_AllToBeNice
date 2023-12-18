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

#pragma once
#ifndef INCLUDE_ATN_GAME_ENEMY_LOGIC_SHOOT
#define INCLUDE_ATN_GAME_ENEMY_LOGIC_SHOOT

#include <glm/glm.hpp>

#include "atn/game/nier_e_airplane/enemy_bullet.h"

namespace atn::game::enemy::logic {

enum class ShootClass {
  Normal,
  Medium,
  Hard,
  Hell,
  Sp3,
  Sp4,
  Sp6
};

class Shoot {
 public:
  Shoot();
  ~Shoot();

 public:
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Attack(
      ShootClass shoot_class, const glm::mat4 &model) const;

 private:
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> NormalAttack(
          const glm::mat4 &model) const;
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> MediumAttack(
          const glm::mat4 &model) const;
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> HardAttack(
          const glm::mat4 &model) const;
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> HellAttack(
          const glm::mat4 &model) const;
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Sp3Attack(
          const glm::mat4 &model) const;
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Sp4Attack(
          const glm::mat4 &model) const;
  std::vector<std::shared_ptr<enemy_bullet::EntityCreateParam>> Sp6Attack(
          const glm::mat4 &model) const;
};

}  // namespace atn::game::enemy::logic

#endif  // !INCLUDE_ATN_GAME_ENEMY_LOGIC_SHOOT
