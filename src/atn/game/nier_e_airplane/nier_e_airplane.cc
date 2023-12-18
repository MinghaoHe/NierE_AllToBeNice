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

#if NIER_E_AIRPLANE

#include <list>
#include <set>
#include <unordered_set>

#include <glm/gtc/matrix_transform.hpp>

#include "atn/game/nier_e_airplane/nier_e_airplane.h"
#include "atn/game/nier_e_airplane/enemy.h"
#include "atn/game/nier_e_airplane/enemy_bullet.h"
#include "atn/game/nier_e_airplane/enemy_hit.h"
#include "atn/game/nier_e_airplane/explosion.h"
#include "atn/game/nier_e_airplane/pod.h"
#include "atn/game/nier_e_airplane/pod_bullet.h"
#include "atn/game/nier_e_airplane/pod_trail.h"

namespace atn {

extern std::shared_ptr<game::CtrlBlock> ggame_block_;

namespace game {

std::unordered_map<std::string, std::unordered_set<std::string>> CollisionRelation() {
  std::unordered_map<std::string, std::unordered_set<std::string>> collision_relation;
  collision_relation[atn::game::kPodBulletTag] = {atn::game::kEnemyBullet, atn::game::kEnemyTag};
  return collision_relation;
}

std::list<std::unique_ptr<engine::ecs::Entity>> OrigSeed() {
  std::list<std::unique_ptr<engine::ecs::Entity>> seed;

  std::shared_ptr<game::pod::EntityCreateParam> pod_param{std::make_shared<game::pod::EntityCreateParam>()};
  seed.emplace_back(game::CreatePod(pod_param));

  return seed;
}

std::unique_ptr<engine::ecs::Entity> CreateEntity(std::shared_ptr<engine::ecs::EntityCreateParam> create_param) {
  const std::unordered_map<std::string, std::function<std::unique_ptr<engine::ecs::Entity>(
      std::shared_ptr<engine::ecs::EntityCreateParam>)>> create_hashmap{
    {game::kEnemyTag, game::CreateEnemy},
    {game::kEnemyBullet, game::CreateEnemyBullet},
    {game::kEnemyHit, game::CreateEnemyHit},
    {game::kExplosion, game::CreateExplosion},
    {game::kPodTag, game::CreatePod},
    {game::kPodBulletTag, game::CreatePodBullet},
    {game::kPodTrailTag, game::CreatePodTrail}
  };
  assert(create_hashmap.contains(create_param->tag));
  return create_hashmap.at(create_param->tag)(create_param);
};

std::string Bgm() { return "res/audio/Weight_of_the_World.mp3"; }

}  // namespace game

}  // namespace atn

#endif
