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
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

using namespace std;

Cube::Cube()
{
    mVertices = make_shared<vector<Vertex3>>();
    mIndices = make_shared<vector<Index>>();
    generateVertices();
    generateIndices();
}

VertexVectorPtr Cube::getVertices() {
    return mVertices;
}

IndexVectorPtr Cube::getIndices() {
    return mIndices;
}

vector<Vertex3> Cube::generateFront()
{
    Color color{0.0f, 1.0f, 1.0f, 1.0f};
    Vector normal{0.0f, 0.0f, 1.0f};
    Position position{-0.5_m, -0.5_m, 0.5_m};
    vector<Vertex3> tmp;
    Vertex3 v{position, color, normal};
    for (int i = 0; i < 4; ++i) {
        tmp.push_back(v);
        v.v0 = Position{glm::rotateZ(v.v0, glm::pi<float>()/2.0f)};
        v.v2 = Vector{glm::rotateZ(v.v2, glm::pi<float>()/2.0f)};
    }
    return tmp;
}

void Cube::generateVertices()
{
    vector<Vertex3> tmp{generateFront()};
    int i = 4;
    while (i--) {
        mVertices->insert(mVertices->end(), tmp.begin(), tmp.end());
        for_each(tmp.begin(), tmp.end(), [](Vertex3& v) {
            v.v0 = Position{glm::rotateY(v.v0, glm::pi<float>()/2.0f)};
            v.v2 = Vector{glm::rotateY(v.v2, glm::pi<float>()/2.0f)};
        });
    }
    for_each(tmp.begin(), tmp.end(), [](Vertex3& v) {
        v.v0 = Position{glm::rotateX(v.v0, glm::pi<float>()/2.0f)};
        v.v2 = Vector{glm::rotateX(v.v2, glm::pi<float>()/2.0f)};
    });
    mVertices->insert(mVertices->end(), tmp.begin(), tmp.end());
    for_each(tmp.begin(), tmp.end(), [](Vertex3& v) {
        v.v0 = Position{glm::rotateX(v.v0, glm::pi<float>())};
        v.v2 = Vector{glm::rotateX(v.v2, glm::pi<float>())};
    });
    mVertices->insert(mVertices->end(), tmp.begin(), tmp.end());
}

void Cube::generateIndices()
{
    constexpr Index verticesPerFace = 4;
    for (Index face = 0; face < 6; ++face) {
        mIndices->push_back(face * verticesPerFace);
        mIndices->push_back(face * verticesPerFace + 1);
        mIndices->push_back(face * verticesPerFace + 2);
        mIndices->push_back(face * verticesPerFace + 2);
        mIndices->push_back(face * verticesPerFace + 3);
        mIndices->push_back(face * verticesPerFace);
    }
}

IndexVectorPtr Triangle::getIndices() {
    IndexVectorPtr v = make_shared<IndexVector>(initializer_list<Index>{2, 1, 0});
    return v;
}

VertexVectorPtr Triangle::getVertices() {
    const Vector normal{0.0f, 0.0f, 1.0f};
    VertexVectorPtr v = make_shared<VertexVector>(initializer_list<Vertex3>{
         Vertex3{Position{-1.0_m, -1.0_m, 0.0_m},
                Color{1.0f, 0.0f, 0.0f, 1.0f}, normal},
         Vertex3{Position{0.0_m, 1.0_m, 0.0_m},
                Color{0.0f, 1.0f, 0.0f, 1.0f}, normal},
         Vertex3{Position{1.0_m, -1.0_m, 0.0_m},
                Color{0.0f, 0.0f, 1.0f, 1.0f}, normal}
    });
    return v;
}
