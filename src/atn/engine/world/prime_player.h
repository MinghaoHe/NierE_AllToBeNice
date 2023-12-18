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
#ifndef INCLUDE_ATN_ENGINE_WORLD_PRIME_PLAYER
#define INCLUDE_ATN_ENGINE_WORLD_PRIME_PLAYER

#include <condition_variable>
#include <thread>

#include "atn/engine/world/world.h"

namespace atn::engine::world {

struct TickLock {
  volatile bool flag{true};
  std::mutex mutex;
  std::condition_variable cv;

  void WakePrimer() { cv.notify_one(); }
  void PrimerSleep() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return flag; });
    flag = false;
  }
  void WakeWorld() { cv.notify_one(); }
  void WorldSleep() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !flag; });
    flag = true;
  }
};

class PrimePlayer final {
 public:
  PrimePlayer(std::shared_ptr<World> world, std::shared_ptr<TickLock> tick_lock);
  ~PrimePlayer();

 public:
  void CreateWorld();
  void CreateEntity(std::shared_ptr<ecs::EntityCreateParam> create_param);
  void DestroyWorld();

 private:
  void CreateMain();
  void CreateEntities();
  void DestroyEntities();

 private:
  std::atomic_bool continue_{true};
  std::thread creator_thread_;

  std::vector<std::shared_ptr<ecs::EntityCreateParam>> to_create_;

  std::shared_ptr<World> world_;
  std::shared_ptr<TickLock> tick_lock_;
};

}  // namespace atn::engine::world

#endif  // !INCLUDE_ATN_ENGINE_WORLD_PRIME_PLAYER
