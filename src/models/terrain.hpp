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
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <memory>
#include "iobject.hpp"
#include "heightmap.hpp"

class Terrain : public IObject
{
public:
    Terrain(const HeightMap& hm);
    virtual ~Terrain();
    VertexVectorPtr getVertices() {
        return mVertices;
    }
    IndexVectorPtr getIndices() {
        return mIndices;
    }

    const GLbyte* verticesData() const {
        return reinterpret_cast<GLbyte*>(mVertices->data());
    }
    GLsizeiptr verticesSize() const {
        return static_cast<GLsizeiptr>(mVertices->size()*sizeof(Vertex3));
    }
    const GLbyte* indicesData() const {
        return reinterpret_cast<GLbyte*>(mIndices->data());
    }
    GLsizeiptr indicesSize() const {
        return static_cast<GLsizeiptr>(mIndices->size()*sizeof(Index));
    }

private:
    void generate(const HeightMap& hm);
    void generateIndices();
    void generateNormals();
    VertexVectorPtr mVertices;
    IndexVectorPtr mIndices;
    unsigned int mWidth;
    unsigned int mHeight;
};

#endif // TERRAIN_HPP
