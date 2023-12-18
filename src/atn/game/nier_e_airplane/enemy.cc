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

#include "enemy.h"

#include "atn/engine/physics/component.h"
#include "atn/game/nier_e_airplane/enemy/audio.h"
#include "atn/game/nier_e_airplane/enemy/logic.h"
#include "atn/game/nier_e_airplane/enemy/render.h"

namespace atn {

extern std::shared_ptr<game::CtrlBlock> ggame_block_;

namespace game {

std::unique_ptr<engine::ecs::Entity> CreateEnemy(std::shared_ptr<engine::ecs::EntityCreateParam> create_param) {
  std::shared_ptr<enemy::EntityCreateParam> create{std::static_pointer_cast<enemy::EntityCreateParam>(create_param)};
  std::unique_ptr<engine::ecs::Entity> enemy{std::make_unique<engine::ecs::Entity>()};

  enemy->Tag(create->tag);

  std::shared_ptr<engine::audio::Component> audio_component{std::make_shared<enemy::AudioComponent>()};
  enemy->Attach(engine::ecs::Category::kAudio, audio_component);

  enemy::LogicCreateParam logic_create{.text{create->text}};
  std::shared_ptr<engine::logic::Component> logic_component{std::make_shared<enemy::LogicComponent>(logic_create)};
  enemy->Attach(engine::ecs::Category::kLogic, logic_component);

  std::shared_ptr<engine::physics::Component> physics_component{std::make_shared<engine::physics::Component>()};
  enemy->Attach(engine::ecs::Category::kPhysics, physics_component);

  std::shared_ptr<engine::render::Component> render_component{std::make_shared<enemy::RenderComponent>()};
  enemy->Attach(engine::ecs::Category::kRender, render_component);

  enemy->Seed()->model = create->model;
  enemy->Seed()->game_block = ggame_block_;

  enemy->Concretize();

  return enemy;
}

}  // namespace game

}  // namespace atn
