/**
 * Copyright (C) 2015, Dariusz Kluska <darkenk@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TEXT_HPP
#define TEXT_HPP

#include "stb_truetype.h"
#include "renderer.hpp"
#include "renderpass.hpp"
#include "units/vertex.hpp"
#include <ImageMagick/Magick++.h>

class Position2D : public glm::vec2
{
public:
    explicit Position2D(Meter _x = 0.0_m, Meter _y = 0.0_m) : glm::vec2{_x, _y} {}
    //explicit Position2D(glm::vec4& v) : glm::vec4{v} {}
    //explicit Position2D(glm::vec4&& v) : glm::vec4{v} {}
    //explicit Position2D(glm::vec3 v) : glm::vec4{v.x, v.y, v.z, 1.0f} {}
//    friend std::ostream& operator<<(std::ostream& o, const Position2D& p) {
//        return o << "p(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
//    }
    static constexpr GLenum Type = GL_FLOAT;
    static constexpr GLint Size = 2;
};

using VertexPosition = Vertex<Position2D>;

class Font 
{
public:
    Font() {
        m_image.read("ExportedFont.bmp");
        m_image.write(&m_blob, "RGBA");
    }
    GLsizei bitmapWidth() {
        return static_cast<GLsizei>(m_image.columns());
    }
    GLsizei bitmapHeight() {
        return static_cast<GLsizei>(m_image.rows());
    }
    const GLvoid* bitmap() {
        return m_blob.data();
    }

private:
    Magick::Image m_image;
    Magick::Blob m_blob;
};

class Text : public IRenderableObject
{
public:
    Text();
    virtual void render();

private:
    Font mFont;
    void init();
    GLuint mFontTex;
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<Buffer<VertexPosition>> mVertexBuffer;
    GLuint mVao;
};
#endif // TEXT_HPP
