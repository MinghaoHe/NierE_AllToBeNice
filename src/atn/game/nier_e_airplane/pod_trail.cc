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

#include "pod_trail.h"

#include "atn/game/nier_e_airplane/pod_trail/logic.h"
#include "atn/game/nier_e_airplane/pod_trail/render.h"
#include "atn/utils/random.h"


namespace atn::game {

std::unique_ptr<engine::ecs::Entity> CreatePodTrail(std::shared_ptr<engine::ecs::EntityCreateParam> create_param) {
  std::shared_ptr<pod_trail::EntityCreateParam> create{std::static_pointer_cast<pod_trail::EntityCreateParam>(create_param)};
  std::unique_ptr<engine::ecs::Entity> pod_trail{std::make_unique<engine::ecs::Entity>()};
  pod_trail->Tag(create->tag);

  std::shared_ptr<engine::logic::Component> logic_component{std::make_shared<pod_trail::LogicComponent>(create->force)};
  pod_trail->Attach(engine::ecs::Category::kLogic, logic_component);

  std::shared_ptr<engine::render::Component> render_component{std::make_shared<pod_trail::RenderComponent>()};
  pod_trail->Attach(engine::ecs::Category::kRender, render_component);

  pod_trail->Seed()->model = create->model;

  pod_trail->Concretize();

  return pod_trail;
}

}  // namespace atn::game
