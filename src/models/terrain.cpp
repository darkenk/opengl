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
#include "terrain.hpp"
#include "logger.hpp"

using namespace std;

Terrain::Terrain(unsigned int width, unsigned int height) :
    mVertices{new VertexVector}, mIndices{new IndexVector}, mWidth{width},
    mHeight{height}
{
    mVertices->reserve(mWidth * mHeight);
    mIndices->reserve(3 * 2 * (mWidth -1) * (mHeight -1));
    generate();
}

VertexVectorPtr Terrain::getVertices()
{
    return mVertices;
}

IndexVectorPtr Terrain::getIndices()
{
    return mIndices;
}

void Terrain::generate()
{
    for (unsigned int y = 0; y < mHeight; y++) {
        for (unsigned int x = 0; x < mWidth; x++) {
            mVertices->push_back(Vertex{Position{static_cast<Meter>(x), 0.0_m,
                                                 static_cast<Meter>(y)},
                                        Color{1.0f, 1.0f, 0.2f, 1.0f},
                                        Vector{0.0f, 1.0f, 0.0f}});
        }
    }
    generateIndices();

}

void Terrain::generateIndices()
{
    unsigned int upperLine;
    unsigned int lowerLine;
    for (GLuint y = 1; y < mHeight; y++) {
        upperLine = (y - 1) * mWidth;
        lowerLine = y * mWidth;
        for (GLuint x = 1; x < mWidth; x++) {
            mIndices->push_back(lowerLine + x);
            mIndices->push_back(upperLine + x);
            mIndices->push_back(upperLine + x - 1);

            mIndices->push_back(lowerLine + x - 1);
            mIndices->push_back(lowerLine + x);
            mIndices->push_back(upperLine + x - 1);
        }
    }
}
