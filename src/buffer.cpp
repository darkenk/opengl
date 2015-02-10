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
#include "buffer.hpp"
#include "logger.hpp"

using namespace std;

template<class T, class Enable = void>
class Offset;

// TODO: quite dirty stuff, used for getting offset of member inside structure
// is anyway to do it better? This code is needed because simple types like int or float
// can't declare desc array, so it's needed to have two different implementations

template<typename T>
class Offset<T, typename std::enable_if<std::is_class<T>::value >::type> {
public:
    GLvoid* getOffset(GLuint member) const { return reinterpret_cast<GLvoid*>(
                    T::desc[static_cast<size_t>(member)]); }
};

template<class T>
class Offset<T, typename std::enable_if<not std::is_class<T>::value >::type> {
public:
    GLvoid* getOffset(GLuint /*member*/) const { return nullptr; }
};

template<typename V, GLenum T>
Buffer<V, T>::Buffer(std::shared_ptr<std::vector<V>> data):
    mData{data}
{
    glGenBuffers(1, &mVertexBufferId);
    bind();
    glBufferData(getTarget(), static_cast<GLsizeiptr>(mData->size() * sizeof(V)),
                 reinterpret_cast<GLbyte*>(mData->data()), GL_STATIC_DRAW);
    unBind();
}

template<typename V, GLenum T>
Buffer<V, T>::~Buffer()
{
    glDeleteBuffers(1, &mVertexBufferId);
}

template<typename V, GLenum T>
void Buffer<V, T>::setAttributes(const AttributeVector& attrs) const
{
    bind();
    GLsizei stride{0};
    for (auto attr : attrs) {
        stride += attr.mFullSize;
    }
    if (stride != sizeof(V)) {
        LOGE << "Stride: " << stride << " is different than sizeof(V) " << sizeof(V);
    }
    // TODO: this offset looks quite dirty
    for (auto attr : attrs) {
        glEnableVertexAttribArray(attr.mLocation);
        glVertexAttribPointer(attr.mLocation, attr.mSize, attr.mType, GL_FALSE,
                              sizeof(V), Offset<V>{}.getOffset(attr.mLocation));
    }
    unBind();
}
