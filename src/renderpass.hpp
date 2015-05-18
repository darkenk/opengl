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
#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include "shader.hpp"
#include <glm/glm.hpp>
#include <memory>

class RenderPass
{
public:
    typedef int Type;
    const static Type SHOW_NORMALS;
    const static Type USER;

    RenderPass(std::shared_ptr<Shader> shader, Type type);
    virtual ~RenderPass();
    virtual void render();

    template<typename V, typename I>
    void setBuffers(const Buffer<V>& vertexBuffer,
                    const Buffer<I, GL_ELEMENT_ARRAY_BUFFER>& indexBuffer) {
        glBindVertexArray(mVao);
        vertexBuffer.setAttributes(*mShader->getAllAttributes());
        vertexBuffer.bind();
        indexBuffer.bind();
        glBindVertexArray(0);
        mNumberOfIndices = indexBuffer.size();
    }

    void setWorldMatrix(const glm::mat4& world);
    void setWvpMatrix(const glm::mat4& mvp);
    Type getType() const { return mType; }
    void enablePoints(bool enable) {
        mDrawPoints = enable;
    }

private:
    std::shared_ptr<Shader> mShader;
    Type mType;
    GLuint mVao;
    GLsizei mNumberOfIndices;
    glm::mat4 mWorld;
    glm::mat4 mWVP;
    bool mDrawPoints;
};

#endif // RENDERPASS_HPP
