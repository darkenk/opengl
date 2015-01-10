/**
 * Copyright (C) 2014, Dariusz Kluska <darkenk@gmail.com>
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
#ifndef COLOUREDOBJECT_H
#define COLOUREDOBJECT_H

#include "irenderableobject.hpp"
#include "shader.hpp"
#include <memory>
#include <GL/glew.h>
#include "iobject.hpp"
#include "buffer.hpp"

class ColouredObject : public IRenderableObject
{
public:
    ColouredObject(std::shared_ptr<IObject> object);
    virtual ~ColouredObject();
    virtual void render();
    virtual void setVpMatrix(glm::mat4& matrix);

private:
    bool createShaders();
    bool releaseShaders();

    std::unique_ptr<Shader> mShader;
    std::shared_ptr<IObject> mObject;
    std::unique_ptr<Buffer<Vertex>> mVertexBuffer;
    std::unique_ptr<Buffer<unsigned int>> mIndexBuffer;
    GLuint mVao;
    GLint mModelId;

    glm::mat4 mModel;
    glm::mat4 mMVP;
};

#endif // TRIANGLEOBJECT_H
