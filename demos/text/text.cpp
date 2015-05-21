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
#include "text.hpp"
#include "exceptions.hpp"
#include <sstream>
#include "stb_truetype.h"
#include "renderer.hpp"
#include "units/vertex.hpp"

using namespace std;

Text::Text()
{
    auto vertices = make_shared<vector<VertexPosition>>();
    vertices->push_back(VertexPosition{Position2D{-0.5_m, -0.5_m}});
//                                       glm::vec3{1.f, 0.f, 0.f}});
    vertices->push_back(VertexPosition{Position2D(0.5_m, -0.5_m)});
//                        glm::vec3{0.0f, 1.f, 0.f}});
    vertices->push_back(VertexPosition{Position2D(-0.5_m, 0.5_m)});
//                        glm::vec3{0.f, 0.f, 1.f}});
    vertices->push_back(VertexPosition{Position2D(0.5_m, 0.5_m)});
//                         glm::vec3{1.f, 1.f, 1.f}});
    
    vector<pair<GLuint, const string>> shaders{
        make_pair(GL_FRAGMENT_SHADER, "text_shaders/fragment.glsl"),
        make_pair(GL_VERTEX_SHADER, "text_shaders/vertex.glsl")};
    mShader = make_shared<Shader>(shaders);
    mVertexBuffer = make_shared<Buffer<VertexPosition>>(vertices);
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
    mVertexBuffer->setAttributes(*mShader->getAllAttributes());
    mVertexBuffer->bind();
    glBindVertexArray(0);
    init();
}

void Text::render()
{
    mShader->use();
    glBindVertexArray(mVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mFontTex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    mShader->unUse();
}

void Text::init()
{
    mShader->use();
    glUniform1i(mShader->getUniform("gTextSampler"), 0);
    glGenTextures(1, &mFontTex);
    glBindTexture(GL_TEXTURE_2D, mFontTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFont.bitmapWidth(), mFont.bitmapHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, mFont.bitmap());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
