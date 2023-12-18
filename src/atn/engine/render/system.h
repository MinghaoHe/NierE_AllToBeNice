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
#ifndef INCLUDE_ATN_ENGINE_RENDER_SYSTEM
#define INCLUDE_ATN_ENGINE_RENDER_SYSTEM

#include <memory>

#include "atn/engine/canvas/sdl_canvas.h"
#include "atn/engine/ecs/system.h"
#include "atn/engine/render/define.h"
#include "atn/engine/render/canvas_frame.h"
#include "atn/engine/render/framebuffer.h"
#include "atn/engine/render/pass.h"
#include "atn/engine/render/text.h"

namespace atn::engine::render {

class System : public ecs::System {
 public:
  explicit System(std::shared_ptr<canvas::SDLCanvas> canvas);
  virtual ~System();

 public:
  virtual void TickPrev(size_t delta) override;
  virtual void TickEntity(size_t delta, std::shared_ptr<ecs::Component> component) override;
  virtual void TickPost(size_t delta) override;

 private:
  void InitPasses();
  void AntiAliasing();
  void ClearFrames();

 private:
  std::shared_ptr<canvas::SDLCanvas> canvas_;

  std::unique_ptr<CanvasFrame> canvas_frame_;
  std::shared_ptr<Framebuffer> main_frame_;
  std::shared_ptr<Text> text_render_;

  std::unordered_map<PassClass, std::unique_ptr<Pass>> render_passes_;
};

}  // namespace atn::engine::render

#endif  // !INCLUDE_ATN_ENGINE_RENDER_SYSTEM
