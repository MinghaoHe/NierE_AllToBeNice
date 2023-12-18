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

#include "system.h"

#include <iostream>

#include "atn/engine/logic/component.h"
#include "atn/game/game.h"

namespace atn::engine::logic {

System::System(int width, int height) : width_(width), height_(height) {}

System::~System() {}

void System::TickPrev(size_t delta) {
  logic::Component::SetUserEvent(mouse_pos_, key_input_);
}

void System::TickEntity(size_t delta, std::shared_ptr<ecs::Component> component) {
  std::shared_ptr<logic::Component> logic{std::dynamic_pointer_cast<logic::Component>(component)};
  const std::string &tag{logic->Tag()};

  logic->Tick(delta);
}

void System::TickPost(size_t delta) {
  game::Tick();
}

void System::OnKeyEvent(SDL_Keycode key, bool is_press) {
  if (is_press) {
    key_input_.insert(key);
  } else {
    key_input_.erase(key);
  }
}

void System::OnMouseMoveEvent(float x, float y) {
  mouse_pos_ = {x / width_ * 2.0f - 1.0f, 1.0f - y / height_ * 2.0f};
}

}  // namespace atn::engine::logic
