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
#include "simpleobject.hpp"
#include "shader.hpp"
#include <iostream>
#include "exceptions.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "logger.hpp"
#include "make_unique.hpp"
#include <algorithm>

using namespace std;

SimpleObject::SimpleObject(shared_ptr<Buffer<Vertex>> vert,
                           shared_ptr<Buffer<Index, GL_ELEMENT_ARRAY_BUFFER>> idx,
                           shared_ptr<Shader> shader):
    mShader{shader}, mVertexBuffer{vert}, mIndexBuffer{idx}
{
    glGetError();

    auto r = make_shared<RenderPass>(shader);
    r->setWorldMatrix(getModel());
    r->setBuffers(*vert, *idx);
    mRenderPasses.push_back(r);

    checkGlError(__FUNCTION__);
}

SimpleObject::~SimpleObject()
{
}

void SimpleObject::render()
{
    for (auto r : mRenderPasses) {
        r->render();
    }
}

void SimpleObject::setVpMatrix(const glm::mat4& matrix)
{
    glm::mat4 wvp = matrix * getModel();
    for (auto r : mRenderPasses) {
        r->setWvpMatrix(wvp);
    }
}

void SimpleObject::addRenderPass(shared_ptr<RenderPass> renderPass)
{
    renderPass->setBuffers(*mVertexBuffer, *mIndexBuffer);
    renderPass->setWorldMatrix(getModel());
    mRenderPasses.push_back(renderPass);
}

void SimpleObject::removeRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    auto pos = find_if(mRenderPasses.begin(), mRenderPasses.end(),
                     [&](shared_ptr<RenderPass> const& r) { return r.get() == renderPass.get(); });
    if (pos != mRenderPasses.end()) {
        mRenderPasses.erase(pos);
    } else {
        LOGE << "Trying remove nonexisted render pass";
    }
}

void SimpleObject::setModel(const glm::mat4& matrix)
{
    IRenderableObject::setModel(matrix);
    for (auto r : mRenderPasses) {
        r->setWorldMatrix(matrix);
    }
}
