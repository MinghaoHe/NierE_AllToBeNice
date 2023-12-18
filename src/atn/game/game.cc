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
#ifndef INCLUDE_ATN_GAME_GAME
#define INCLUDE_ATN_GAME_GAME

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "atn/engine/ecs/entity.h"


#define NIER_E_AIRPLANE 1

#if NIER_E_AIRPLANE

#include "atn/game/nier_e_airplane/nier_e_airplane.h"

#else

namespace atn::game {

inline std::unordered_map<std::string, std::unordered_set<std::string>> CollisionRelation() {
  return {};
}

inline std::list<std::unique_ptr<engine::ecs::Entity>> OrigSeed() {
  return {};
}

inline std::unique_ptr<engine::ecs::Entity> CreateEntity(std::shared_ptr<engine::ecs::EntityCreateParam> create_param) {
  return std::make_unique<engine::ecs::Entity>();
}

inline std::string Bgm() { return {}; }

inline void Control() {}

}  // namespace atn::game

#endif

#endif  // !INCLUDE_ATN_GAME_GAME
