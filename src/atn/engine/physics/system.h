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
#ifndef INCLUDE_ATN_ENGINE_PHYSICS_SYSTEM
#define INCLUDE_ATN_ENGINE_PHYSICS_SYSTEM

#include <unordered_set>

#include "atn/engine/ecs/entity.h"
#include "atn/engine/ecs/system.h"
#include "atn/engine/physics/component.h"

namespace atn::engine::physics {

class System : public ecs::System {
 public:
  System();

  virtual ~System();

 public:
  virtual void TickPrev(size_t delta) override;
  virtual void TickEntity(size_t delta, std::shared_ptr<ecs::Component> component) override;
  virtual void TickPost(size_t delta) override;

 public:
  void AddCollisionRelation(const std::string &collider, const std::unordered_set<std::string> &collidee);

 private:
  void Divide(std::shared_ptr<physics::Component> component);
  void CollisionDetect(const std::vector<std::shared_ptr<physics::Component>> &components);
  bool Intersect(const Box &collider_box, const glm::mat4 &collider_model,
                 const Box &collidee_box, const glm::mat4 &collidee_model) const;
  bool RCIntersect(const Box &collider_box, const glm::mat4 &collider_model,
                   const Box &collidee_box, const glm::mat4 &collidee_model) const;
  bool RRIntersect(const Box &collider_box, const glm::mat4 &collider_model,
                   const Box &collidee_box, const glm::mat4 &collidee_model) const;
 private:
  std::unordered_map<std::string, std::unordered_set<std::string>> collision_relation_;
  std::array<std::vector<std::shared_ptr<physics::Component>>, 5> quadrant_;
};

}  // namespace atn::engine::physics

#endif  // !INCLUDE_ATN_ENGINE_PHYSICS_SYSTEM
