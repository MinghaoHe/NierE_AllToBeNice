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

#include "text.h"

#include <ranges>

#include <freetype/freetype.h>

namespace atn::engine::render {

Text::Text() { GenCharTextures(); }

Text::~Text() { DelCharTextures(); }

const Character& Text::CharFont(char c) const { return character_textures_.at(c); }

void Text::GenCharTextures() {
  FT_Library ft{};
  FT_Face ft_face{};

  FT_Init_FreeType(&ft);
  FT_New_Face(ft, "res/font/Prida01.otf", 0, &ft_face);
  FT_Set_Pixel_Sizes(ft_face, 0, 48);

  GLint pre_align{4};
  glGetIntegerv(GL_UNPACK_ALIGNMENT, &pre_align);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (FT_ULong c{0}; c < 128; ++c) {
    FT_Load_Char(ft_face, c, FT_LOAD_RENDER);
    GLuint texture{0};
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, ft_face->glyph->bitmap.width,
                 ft_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 ft_face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character{
        .texture = texture,
        .size{ft_face->glyph->bitmap.width,
              ft_face->glyph->bitmap.rows},
        .bearing{ft_face->glyph->bitmap_left,
                 ft_face->glyph->bitmap_top},
        .advance = static_cast<unsigned int>(ft_face->glyph->advance.x)};
    character_textures_[static_cast<char>(c)] = character;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, pre_align);

  FT_Done_Face(ft_face);
  FT_Done_FreeType(ft);
}

void Text::DelCharTextures() {
  for (const Character &c : character_textures_ | std::views::values) {
    glDeleteTextures(1, &c.texture);
  }
  character_textures_.clear();
}

}  // namespace atn::engine::render
