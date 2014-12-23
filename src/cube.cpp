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
#include "cube.hpp"
#include <vector>

using namespace std;

Cube::Cube()
{
}

VertexVectorPtr Cube::getVertices() {
    VertexVectorPtr v = VertexVectorPtr(new vector<Vertex> ({
        Vertex( glm::vec4(-0.5f, 0.5f, -0.5f, 1.0),
                glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex( glm::vec4( 0.5f, 0.5f, -0.5f, 1.0),
                glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex( glm::vec4(-0.5f, -0.5f,-0.5f, 1.0),
                glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
        Vertex( glm::vec4( 0.5f, -0.5f,-0.5f, 1.0), //3
                glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
        Vertex( glm::vec4(-0.5f, 0.5f,  0.5f, 1.0), //
                glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)),
        Vertex( glm::vec4( 0.5f, 0.5f,  0.5f, 1.0),
                glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)),
        Vertex( glm::vec4(-0.5f, -0.5f, 0.5f, 1.0),
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        Vertex( glm::vec4( 0.5f, -0.5f, 0.5f, 1.0), //7
                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
    }));
    return v;
}

IndexVectorPtr Cube::getIndices() {
    IndexVectorPtr v = IndexVectorPtr(new vector<unsigned int>({
        1, 0, 2,
        1, 2, 3,
        5, 4, 6,
        5, 6, 7,
        1, 5, 7,
        1, 7, 3,
        0, 4, 6,
        0, 6, 2,
        0, 4, 5,
        5, 1, 0,
        2, 6, 7,
        2, 7, 3
    }));
    return v;
}


IndexVectorPtr Triangle::getIndices() {
    IndexVectorPtr v = IndexVectorPtr(new vector<unsigned int>({
                                                                   1, 2, 0
                                                               }));
    return v;
}


VertexVectorPtr Triangle::getVertices() {
    VertexVectorPtr v = VertexVectorPtr{new std::vector<Vertex> {
                                                                     //setup triangle geometry
                                                                     Vertex( glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f),
                                                                     glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
                                                                     Vertex( glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                                                     glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
                                                                     Vertex( glm::vec4(1.0f, -1.0f, 0.0f, 1.0f),
                                                                     glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
                                                                 }};
                                                                 return v;
}
