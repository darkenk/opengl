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
#ifndef SIMPLEOBJECT_HPP
#define SIMPLEOBJECT_HPP

#include <memory>
#include <GL/glew.h>
#include "irenderableobject.hpp"
#include "shader.hpp"
#include "iobject.hpp"
#include "buffer.hpp"
#include "renderpass.hpp"
#include "units/vertex.hpp"

class SimpleObject : public IRenderableObject
{
public:
    SimpleObject(std::shared_ptr<Buffer<Vertex3>> vert,
                 std::shared_ptr<Buffer<Index, GL_ELEMENT_ARRAY_BUFFER>> idx,
                 std::shared_ptr<Shader> shader);
    virtual ~SimpleObject();
    virtual void render();
    virtual void setVpMatrix(const glm::mat4& matrix);
    virtual void addRenderPass(std::shared_ptr<RenderPass> renderPass);
    virtual void removeRenderPass(RenderPass::Type t);
    virtual void setModel(const glm::mat4& matrix);

private:
    std::shared_ptr<Shader> mShader;
    std::vector<std::shared_ptr<RenderPass>> mRenderPasses;
    std::shared_ptr<Buffer<Vertex3>> mVertexBuffer;
    std::shared_ptr<Buffer<Index, GL_ELEMENT_ARRAY_BUFFER>> mIndexBuffer;
};

#endif // SIMPLEOBJECT_HPP
