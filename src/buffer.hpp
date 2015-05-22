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
#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <GL/glew.h>
#include <string>
#include <ostream>
#include <vector>
#include <memory>
#include "logger.hpp"

class Attribute
{
public:
    Attribute(GLuint index, GLchar* name, GLint fullSize, GLuint location):
        mIndex{index}, mFullSize(fullSize), mName{name}, mLocation{location} {}

    GLuint mIndex;
    GLint mFullSize;
    std::string mName;
    GLuint mLocation;

    friend std::ostream& operator<<(std::ostream& of, const Attribute& attr) {
        return of << "Attrib: " << attr.mName << " idx: " << attr.mIndex
                  << " fullSize: " << attr.mFullSize << " location: " << attr.mLocation;
    }
};

typedef std::vector<Attribute> AttributeVector;
typedef std::shared_ptr<AttributeVector> AttributeVectorPtr;

template<typename V, GLenum T = GL_ARRAY_BUFFER>
class Buffer
{
public:
    Buffer(std::shared_ptr<std::vector<V>> data): mData{data} {
        glGenBuffers(1, &mVertexBufferId);
        bind();
        glBufferData(getTarget(), static_cast<GLsizeiptr>(mData->size() * sizeof(V)),
                     reinterpret_cast<GLbyte*>(mData->data()), GL_STATIC_DRAW);
        unBind();
    }

    ~Buffer() {
        glDeleteBuffers(1, &mVertexBufferId);
    }

    void bind() const {
        glBindBuffer(getTarget(), mVertexBufferId);
    }
    void unBind() const {
        glBindBuffer(getTarget(), 0);
    }
    void setAttributes(const AttributeVector& attrs) const {
        bind();
        GLsizei stride{0};
        for (auto attr : attrs) {
            stride += attr.mFullSize;
        }
        if (stride != sizeof(V)) {
            LOGE << "Stride: " << stride << " is different than sizeof(V) " << sizeof(V);
        }
        for (auto attr : attrs) {
            glEnableVertexAttribArray(attr.mLocation);
            glVertexAttribPointer(attr.mLocation, V::getSize(attr.mLocation),
                                  V::getType(attr.mLocation), GL_FALSE, sizeof(V),
                                  reinterpret_cast<void*>(V::getOffset(attr.mLocation)));
        }
        unBind();
    }
    GLsizei size() const {
        return static_cast<GLsizei>(mData->size());
    }
    constexpr GLenum getTarget() const { return T; }

private:
    GLuint mVertexBufferId;
    std::shared_ptr<std::vector<V>> mData;
};

#endif // BUFFER_HPP
