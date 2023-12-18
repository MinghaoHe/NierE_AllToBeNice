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

#pragma once
#ifndef INCLUDE_ATN_GAME_POD_BULLET
#define INCLUDE_ATN_GAME_POD_BULLET

#include <glm/glm.hpp>

#include "atn/engine/ecs/entity.h"
#include "atn/game/nier_e_airplane/tag.h"

namespace atn::game {

namespace pod_bullet {

struct EntityCreateParam : public engine::ecs::EntityCreateParam {
  glm::mat4 model{1.0f};
  explicit EntityCreateParam() : engine::ecs::EntityCreateParam(kPodBulletTag) {}
};

}  // namespace pod_bullet

std::unique_ptr<engine::ecs::Entity> CreatePodBullet(std::shared_ptr<engine::ecs::EntityCreateParam> create_param);

}  // namespace atn::game

#endif  // !INCLUDE_ATN_GAME_POD_BULLET