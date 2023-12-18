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

#include "enemy_bullet.h"

#include "atn/engine/physics/component.h"
#include "atn/game/nier_e_airplane/enemy_bullet/logic.h"
#include "atn/game/nier_e_airplane/enemy_bullet/render.h"

namespace atn::game {

std::unique_ptr<engine::ecs::Entity> CreateEnemyBullet(std::shared_ptr<engine::ecs::EntityCreateParam> create_param) {
  std::shared_ptr<enemy_bullet::EntityCreateParam> create{std::static_pointer_cast<enemy_bullet::EntityCreateParam>(create_param)};
  std::unique_ptr<engine::ecs::Entity> enemy_bullet{std::make_unique<engine::ecs::Entity>()};

  enemy_bullet->Tag(create->tag);

  enemy_bullet::LogicCreateParam logic_create{.speed = create->speed};
  std::shared_ptr<engine::logic::Component> logic_component{std::make_shared<enemy_bullet::LogicComponent>(logic_create)};
  enemy_bullet->Attach(engine::ecs::Category::kLogic, logic_component);

  if (create->collision) {
    std::shared_ptr<engine::physics::Component> physics_component{std::make_shared<engine::physics::Component>()};
    enemy_bullet->Attach(engine::ecs::Category::kPhysics, physics_component);
  }

  enemy_bullet::RenderCreateParam render_create{.color = create->color};
  std::shared_ptr<engine::render::Component> render_component{std::make_shared<enemy_bullet::RenderComponent>(render_create)};
  enemy_bullet->Attach(engine::ecs::Category::kRender, render_component);

  enemy_bullet->Seed()->model = create->model;

  enemy_bullet->Concretize();

  return enemy_bullet;
}

}  // namespace atn::game
