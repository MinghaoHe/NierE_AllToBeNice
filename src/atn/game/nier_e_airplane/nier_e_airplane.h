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
#ifndef INCLUDE_ATN_GAME_NIER_E_AIRPLANE
#define INCLUDE_ATN_GAME_NIER_E_AIRPLANE

#include <list>
#include <set>
#include <unordered_set>

#include "atn/game/nier_e_airplane/tag.h"

#include "atn/game/nier_e_airplane/enemy.h"
#include "atn/game/nier_e_airplane/enemy_bullet.h"
#include "atn/game/nier_e_airplane/enemy_hit.h"
#include "atn/game/nier_e_airplane/particle.h"
#include "atn/game/nier_e_airplane/pod.h"
#include "atn/game/nier_e_airplane/pod_bullet.h"
#include "atn/game/nier_e_airplane/pod_trail.h"

namespace atn::game {

inline std::unordered_map<std::string, std::unordered_set<std::string>> CollisionRelation() {
  std::unordered_map<std::string, std::unordered_set<std::string>> collision_relation;
  collision_relation[atn::game::kPodBulletTag] = {atn::game::kEnemyBullet, atn::game::kEnemyTag};
  return collision_relation;
}

inline std::list<std::unique_ptr<engine::ecs::Entity>> OrigSeed() {
  std::list<std::unique_ptr<engine::ecs::Entity>> seed;

  std::shared_ptr<game::pod::EntityCreateParam> pod_param{std::make_shared<game::pod::EntityCreateParam>()};
  seed.emplace_back(game::CreatePod(pod_param));

  std::shared_ptr<game::enemy::EntityCreateParam> enemy_param{std::make_shared<game::enemy::EntityCreateParam>()};
  enemy_param->text = "MinghaoHe";
  seed.emplace_back(game::CreateEnemy(enemy_param));

  std::shared_ptr<game::enemy_hit::EntityCreateParam> enemy_hit_param{std::make_shared<game::enemy_hit::EntityCreateParam>()};
  seed.emplace_back(game::CreateEnemyHit(enemy_hit_param));

  return seed;
}


inline std::unique_ptr<engine::ecs::Entity> CreateEntity(std::shared_ptr<engine::ecs::EntityCreateParam> create_param) {
  std::unique_ptr<engine::ecs::Entity> entity;
  if (create_param->tag.compare(game::kEnemyTag) == 0) {
    entity = game::CreateEnemy(create_param);
  } else if (create_param->tag.compare(game::kEnemyBullet) == 0) {
    entity = game::CreateEnemyBullet(create_param);
  } else if (create_param->tag.compare(game::kEnemyHit) == 0) {
    entity = game::CreateEnemyHit(create_param);
  } else if (create_param->tag.compare(game::kParticle) == 0) {
    entity = game::CreateParticle(create_param);
  } else if (create_param->tag.compare(game::kPodTag) == 0) {
    entity = game::CreatePod(create_param);
  } else if (create_param->tag.compare(game::kPodBulletTag) == 0) {
    entity = game::CreatePodBullet(create_param);
  } else if (create_param->tag.compare(game::kPodTrailTag) == 0) {
    entity = game::CreatePodTrail(create_param);
  }
  return std::move(entity);
};

inline std::string Bgm() { return "res/audio/Weight_of_the_World.mp3"; }

}  // namespace atn::game

#endif  // !INCLUDE_ATN_GAME_NIER_E_AIRPLANE
