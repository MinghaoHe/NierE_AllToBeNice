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
#ifndef INCLUDE_ATN_ENGINE_RENDER_PASS
#define INCLUDE_ATN_ENGINE_RENDER_PASS

#include <memory>
#include <string>
#include <unordered_map>

#include "atn/engine/render/define.h"
#include "atn/engine/render/framebuffer.h"
#include "atn/engine/render/object.h"

namespace atn::engine::render {

class Pass {
 public:
  explicit Pass(std::shared_ptr<Framebuffer> main_frame);
  virtual ~Pass();

 public:
  virtual void PrevDraw(size_t delta) = 0;
  virtual void Draw(const std::string &tag,
                    std::shared_ptr<PassData> pass_data, size_t delta) = 0;
  virtual GLuint PostDraw(size_t delta) = 0;

 protected:
  std::shared_ptr<Framebuffer> main_frame_;
  std::unordered_map<std::string, RdrObj> rdr_objs_;
};

}  // namespace atn::engine::render

#endif  // !INCLUDE_ATN_ENGINE_RENDER_PASS
