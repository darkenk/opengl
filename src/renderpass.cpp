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
#include "renderpass.hpp"
#include <glm/gtc/type_ptr.hpp>

const RenderPass::Type RenderPass::SHOW_NORMALS = 0;
const RenderPass::Type RenderPass::USER = 100;

RenderPass::RenderPass(std::shared_ptr<Shader> shader, Type type) :
    mShader{shader}, mType{type}, mDrawPoints{false}
{
    glGenVertexArrays(1, &mVao);
}

RenderPass::~RenderPass()
{
    glDeleteVertexArrays(1, &mVao);
}

void RenderPass::render()
{
    mShader->use();
    glUniformMatrix4fv(mShader->getUniform("gWorld"), 1, GL_FALSE, glm::value_ptr(mWorld));
    glUniformMatrix4fv(mShader->getUniform("gWVP"), 1, GL_FALSE, glm::value_ptr(mWVP));
    glBindVertexArray(mVao);
    if (mDrawPoints) {
        glPointSize(4.0f);
        glDrawArrays(GL_POINTS, 0, mNumberOfIndices/3);
    } else {
        glDrawElements(GL_TRIANGLES, mNumberOfIndices, GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);
    mShader->unUse();
}

void RenderPass::setWorldMatrix(const glm::mat4& world)
{
    mWorld = world;
}

void RenderPass::setWvpMatrix(const glm::mat4& wvp)
{
    mWVP = wvp;
}
