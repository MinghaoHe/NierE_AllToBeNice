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

#include "component.h"

namespace atn::engine::physics {

Component::Component() {}

Component::~Component() {}

void Component::Tick(size_t delta) {
  if (bounding_box_.box_class != BoxClass::None) return;
  if (!seed_->logic.contains("box_class")) return;

  bounding_box_.box_class = seed_->logic["box_class"];

  if (bounding_box_.box_class == BoxClass::Circle) {
    if (seed_->logic.contains("radius")) {
      bounding_box_.box = CircleBox{.r = seed_->logic["radius"]};
    }
  } else if (bounding_box_.box_class == BoxClass::Rectangle) {
    if (seed_->logic.contains("width") && seed_->logic.contains("height")) {
      float w = seed_->logic["width"].get<float>() / 2.0f;
      float h = seed_->logic["height"].get<float>() / 2.0f;
      bounding_box_.box = engine::physics::RectBox{.vertices = {glm::vec4{ w,  h, 0.0f, 1.0f},
                                                                glm::vec4{-w,  h, 0.0f, 1.0f},
                                                                glm::vec4{-w, -h, 0.0f, 1.0f},
                                                                glm::vec4{ w, -h, 0.0f, 1.0f}}};
    }
  }
}

const Box &Component::BoundingBox() const {
  return bounding_box_;
}

void Component::Collide(const std::string &tag) {
  seed_->logic["collision"] = tag;
}

}  // namespace atn::engine::physics
