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
#ifndef INCLUDE_ATN_ENGINE
#define INCLUDE_ATN_ENGINE

#include <memory>
#include <unordered_map>

#include "atn/engine/canvas/sdl_canvas.h"
#include "atn/engine/ecs/system.h"
#include "atn/engine/world/prime_player.h"
#include "atn/engine/world/world.h"

namespace atn {

using namespace engine;

class Engine final {
 public:
  Engine(int argc, char *argv[]);
  ~Engine();

 public:
  void Initialize();
  void CreateWorld();
  int Exec();

 private:
  void MakeCanvas(int width, int height);
  bool Continue();
  void Tick();
  void PollEvent();
  void LoadWorld();

 private:
  size_t delta_{0};
  volatile bool continue_{true};
  std::shared_ptr<World> world_;
  std::shared_ptr<game::CtrlBlock> game_block_;
  std::shared_ptr<world::TickLock> tick_lock_;
  std::shared_ptr<world::PrimePlayer> primer_;
  std::shared_ptr<canvas::SDLCanvas> canvas_;

  std::unordered_map<ecs::Category, std::shared_ptr<ecs::System>> systems_;
};

}  // namespace atn

#endif  // !INCLUDE_ATN_ENGINE
