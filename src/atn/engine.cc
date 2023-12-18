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

#include "engine.h"

#include <chrono>
#include <filesystem>
#include <thread>

#include "atn/define.h"
#include "atn/engine/audio/system.h"
#include "atn/engine/logic/system.h"
#include "atn/engine/physics/system.h"
#include "atn/engine/render/system.h"

namespace atn {

using namespace engine;

std::weak_ptr<world::PrimePlayer> gprimer_;
std::shared_ptr<game::CtrlBlock> ggame_block_;

Engine::Engine(int argc, char *argv[]) {
  std::filesystem::current_path(std::filesystem::canonical(argv[0]).parent_path());
}

Engine::~Engine() {}

void Engine::Initialize() {
  MakeCanvas(kWidth, kHeight);
  systems_[ecs::Category::kAudio] = std::make_shared<audio::System>();
  systems_[ecs::Category::kLogic] = std::make_shared<logic::System>(kWidth, kHeight);
  systems_[ecs::Category::kPhysics] = std::make_shared<physics::System>();
  systems_[ecs::Category::kRender] = std::make_shared<render::System>(canvas_);

}

void Engine::CreateWorld() {
  game_block_ = std::make_shared<game::CtrlBlock>();
  ggame_block_ = game_block_;
  world_ = std::make_shared<World>();
  tick_lock_ = std::make_shared<world::TickLock>();

  primer_ = std::make_shared<world::PrimePlayer>(world_, tick_lock_);
  gprimer_ = primer_;

  primer_->CreateWorld();
}

int Engine::Exec() {
  while (Continue()) {
    Tick();
  }
  primer_->DestroyWorld();
  ggame_block_.reset();

  canvas_->Destroy();
  return 0;
}

void Engine::MakeCanvas(int width, int height) {
  canvas_ = std::make_shared<canvas::SDLCanvas>();

  canvas::CreateParam canvas_param{.size{width, height},
                                   .name{kDisplayName}};

  canvas_->Create(canvas_param);
}

bool Engine::Continue() {
  const static size_t kExpectedDelta{1000 / kFps};
  static auto now{std::chrono::steady_clock::now()};

  delta_ = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now() - now).count();

  tick_lock_->WakePrimer();

  if (delta_ < kExpectedDelta) {
    std::this_thread::sleep_for(std::chrono::milliseconds(kExpectedDelta - delta_));
    delta_ = kExpectedDelta;
  }

  tick_lock_->WorldSleep();

  now = std::chrono::steady_clock::now();

  return continue_;
}

void Engine::Tick() {
  PollEvent();

  for (auto &[category, system] : systems_) {
    system->TickPrev(delta_);
    for (auto &entity : world_->Entities()) {
      auto component{entity->Appear(category)};
      if (!component.has_value()) continue;

      system->TickEntity(delta_, component.value());
    }
    system->TickPost(delta_);
  }
}

void Engine::PollEvent() {
  std::shared_ptr<logic::System> logic_system =
          std::dynamic_pointer_cast<logic::System>(systems_[ecs::Category::kLogic]);
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT: {
        continue_ = false;
      } break;
      case SDL_EVENT_KEY_DOWN: {
        logic_system->OnKeyEvent(event.key.keysym.sym, true);
      } break;
      case SDL_EVENT_KEY_UP: {
        logic_system->OnKeyEvent(event.key.keysym.sym, false);
      } break;
      case SDL_EVENT_MOUSE_MOTION: {
        logic_system->OnMouseMoveEvent(event.motion.x, event.motion.y);
      } break;
    }
  }
}

void Engine::LoadWorld() {

}

}  // namespace atn
