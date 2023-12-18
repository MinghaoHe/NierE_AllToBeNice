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

#include "entity.h"

#include "atn/utils/id_generator.h"

namespace atn::engine::ecs {

Entity::Entity() { seed_ = std::make_shared<EntitySeed>(); }

Entity::~Entity() {}

std::string Entity::Tag() const {
  return seed_->tag;
}

void Entity::Tag(const std::string &tag) { seed_->tag = tag; }

std::shared_ptr<EntitySeed> Entity::Seed() { return seed_; }

void Entity::Concretize() { seed_->id = utils::IdGenerator::Alloc(); }

void Entity::Dissipate() { utils::IdGenerator::Free(seed_->id); }

void Entity::Attach(Category category, std::shared_ptr<Component> component) {
  component->Seed(seed_);
  appearance_[category] = component;
}

std::optional<std::shared_ptr<Component>> Entity::Appear(Category category) const {
  if (!appearance_.contains(category)) {
    return std::nullopt;
  }
  return appearance_.at(category);
}

}  // namespace atn::engine::ecs
