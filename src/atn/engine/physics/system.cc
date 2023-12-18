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

#include "system.h"

#include <glm/glm.hpp>

#include "atn/engine/physics/component.h"
#include "atn/game/game.h"

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace atn::engine::physics {

System::System() {
  for (auto &c : game::CollisionRelation()) {
    AddCollisionRelation(c.first, c.second);
  }
}

System::~System() {}

void System::TickPrev(size_t delta) {
  for (auto &list : quadrant_) {
    list.clear();
  }
}

void System::TickEntity(size_t delta, std::shared_ptr<ecs::Component> component) {
  component->Tick(delta);
  Divide(std::dynamic_pointer_cast<physics::Component>(component));
}

void System::TickPost(size_t delta) {
  for (const auto &components : quadrant_) {
    CollisionDetect(components);
  }
}

void System::AddCollisionRelation(const std::string &collider, const std::unordered_set<std::string> &collidee) {
  collision_relation_.insert({collider, collidee});
}

void System::Divide(std::shared_ptr<physics::Component> component) {
  std::shared_ptr<physics::Component> physics{std::dynamic_pointer_cast<physics::Component>(component)};
  glm::vec3 pos = physics->Seed()->model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

  if (pos.x >= 0.0f && pos.y >= 0.0f) {
    quadrant_[0].push_back(component);
  }
  if (pos.x < 0.0f && pos.y >= 0.0f) {
    quadrant_[1].push_back(component);
  }
  if (pos.x < 0.0f && pos.y < 0.0f) {
    quadrant_[2].push_back(component);
  }
  if (pos.x >= 0.0f && pos.y < 0.0f) {
    quadrant_[3].push_back(component);
  }
  if (pos.x < 0.5f && pos.x > -0.5 && pos.y < 0.5f && pos.y > -0.5) {
    quadrant_[4].push_back(component);
  }
}

void System::CollisionDetect(const std::vector<std::shared_ptr<physics::Component>> &components) {
  for (const auto &collision_relation : collision_relation_) {
    for (auto &collider : components) {
      if (collider->Tag().compare(collision_relation.first) != 0) continue;
      for (auto &collidee : components) {
        if (collider == collidee ||
            !collision_relation_[collider->Tag()].contains(collidee->Tag()))
          continue;
        if (Intersect(collider->BoundingBox(), collider->Seed()->model,
                      collidee->BoundingBox(), collidee->Seed()->model)) {
          collider->Collide(collidee->Tag());
          collidee->Collide(collidee->Tag());
        }
      }
    }
  }
}

bool System::Intersect(const Box &collider_box, const glm::mat4 &collider_model,
                       const Box &collidee_box, const glm::mat4 &collidee_model) const {
  if (collider_box.box_class == BoxClass::Rectangle &&
      collidee_box.box_class == BoxClass::Circle) {
    return RCIntersect(collider_box, collider_model, collidee_box, collidee_model);
  } else if (collider_box.box_class == BoxClass::Rectangle &&
             collidee_box.box_class == BoxClass::Rectangle) {
    return RRIntersect(collider_box, collider_model, collidee_box, collidee_model);
  }
  return false;
}

bool System::RCIntersect(const Box &collider_box, const glm::mat4 &collider_model,
                 const Box &collidee_box, const glm::mat4 &collidee_model) const {
  glm::vec4 collidee_pos = collidee_model * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
  for (const glm::vec4 &pos :
          std::get<RectBox>(collider_box.box).vertices) {
    if (glm::length(collidee_pos - collider_model * pos) <
        std::get<CircleBox>(collidee_box.box).r) {
      return true;
    }
  }
  return false;
}

bool System::RRIntersect(const Box &collider_box, const glm::mat4 &collider_model,
                         const Box &collidee_box, const glm::mat4 &collidee_model) const {
  glm::vec2 collidee_min{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
  glm::vec2 collidee_max{std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
  for (const glm::vec4 &vertex : std::get<RectBox>(collidee_box.box).vertices) {
    glm::vec4 collidee_pos = collidee_model * vertex;
    collidee_max.x = std::max(collidee_pos.x, collidee_max.x);
    collidee_max.y = std::max(collidee_pos.y, collidee_max.y);
    collidee_min.x = std::min(collidee_pos.x, collidee_min.x);
    collidee_min.y  = std::min(collidee_pos.y, collidee_min.y);
  }
  for (const glm::vec4 &vertex : std::get<RectBox>(collider_box.box).vertices) {
    glm::vec4 collider_pos = collider_model * vertex;
    if (collider_pos.x > collidee_min.x && collider_pos.x < collidee_max.x &&
        collider_pos.y > collidee_min.y && collider_pos.y < collidee_max.y) {
      return true;
    }
  }

  glm::vec4 collider_pos{};
  for (const glm::vec4 &vertex : std::get<RectBox>(collider_box.box).vertices) {
    collider_pos += collider_model * vertex;
  }
  collider_pos = collider_pos * 0.25f;
  if (collider_pos.x > collidee_min.x && collider_pos.x < collidee_max.x &&
      collider_pos.y > collidee_min.y && collider_pos.y < collidee_max.y) {
    return true;
  }

  return false;
}

}  // namespace atn::engine::physics
