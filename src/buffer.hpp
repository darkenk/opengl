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

class Attribute
{
public:
    Attribute(GLuint index, GLint size, GLenum type, GLchar* name, GLint fullSize, GLuint location):
        mIndex{index}, mSize{size}, mType{type}, mFullSize(fullSize), mName{name},
        mLocation{location} {}

    GLuint mIndex;
    GLint mSize;
    GLenum mType;
    GLint mFullSize;
    std::string mName;
    GLuint mLocation;

    friend std::ostream& operator<<(std::ostream& of, const Attribute& attr) {
        return of << "Attrib: " << attr.mName << " idx: " << attr.mIndex << std::hex
                  << " type: " << attr.mType << " size: " << attr.mSize << std::dec
                  << " fullSize: " << attr.mFullSize << " location: " << attr.mLocation;
    }
};

typedef std::vector<Attribute> AttributeVector;
typedef std::shared_ptr<AttributeVector> AttributeVectorPtr;

template<typename T>
class Buffer
{
public:
    Buffer(std::shared_ptr<std::vector<T>> data, GLenum target = GL_ARRAY_BUFFER);
    ~Buffer();
    void bind();
    void unBind();
    void setAttributes(const AttributeVector& attrs);
    GLsizei size();

private:
    GLuint mVertexBufferId;
    std::shared_ptr<std::vector<T>> mData;
    GLenum mTarget;
};

#endif // BUFFER_HPP
