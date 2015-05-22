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
#include "sphere.hpp"
#include <glm/common.hpp>
#include "../logger.hpp"
#include <algorithm>

using namespace std;

Sphere::Sphere(uint32_t level, Color color):
    mLevel{level}, mColor{color}
{
    mVertices = make_shared<vector<Vertex3>>();
    mIndices = make_shared<vector<Index>>();
    generateVertices();
    generateIndices();
    increaseLevelOfDetail();
    computeNormals();
}

VertexVectorPtr Sphere::getVertices() {
    return mVertices;
}

IndexVectorPtr Sphere::getIndices() {
    return mIndices;
}

void Sphere::generateVertices()
{
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(0.0_m, 1.0_m, 1.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(0.0_m, 1.0_m, -1.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(0.0_m, -1.0_m, 1.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(0.0_m, -1.0_m, -1.0_m))}, mColor});

    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(1.0_m, -1.0_m, 0.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(1.0_m, 1.0_m, 0.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(-1.0_m, -1.0_m, 0.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(-1.0_m, 1.0_m, 0.0_m))}, mColor});

    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(-1.0_m, 0.0_m, -1.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(1.0_m, 0.0_m, -1.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(-1.0_m, 0.0_m, 1.0_m))}, mColor});
    mVertices->push_back(Vertex3{Position{glm::normalize(glm::vec3(1.0_m, 0.0_m, 1.0_m))}, mColor});
}

void Sphere::increaseLevelOfDetail()
{
    for (uint32_t i = 0; i < mLevel; i++) {
        auto idx = mIndices;
        mIndices = make_shared<vector<Index>>();
        for (uint32_t j = 0; j < idx->size();) {
            auto v1 = idx->at(j++);
            auto v2 = idx->at(j++);
            auto v3 = idx->at(j++);
            auto a = getMiddlePoint(v1, v2);
            auto b = getMiddlePoint(v2, v3);
            auto c = getMiddlePoint(v3, v1);
            addTriangleIdx(v1, a, c);
            addTriangleIdx(v2, b, a);
            addTriangleIdx(v3, c, b);
            addTriangleIdx(a, b, c);
        }
    }
}

void Sphere::computeNormals()
{
    auto vertexNormals = make_shared<vector<glm::vec3>>(mVertices->size());
    for (uint32_t i = 0; i < mIndices->size();) {
        auto v1 = mIndices->at(i++);
        auto v2 = mIndices->at(i++);
        auto v3 = mIndices->at(i++);
        auto a = mVertices->at(v1).v0;
        auto b = mVertices->at(v2).v0;
        auto c = mVertices->at(v3).v0;
        auto f1 = glm::normalize(glm::cross(glm::vec3(b - c), glm::vec3(b - a)));
        vertexNormals->at(v1) += f1;
        vertexNormals->at(v2) += f1;
        vertexNormals->at(v3) += f1;
    }
    for (uint32_t i = 0; i < mVertices->size(); i++) {
        mVertices->at(i).v2 = Vector{glm::normalize(vertexNormals->at(i))};
    }
}

void Sphere::generateIndices()
{
    // 5 adjacent in 0
    addTriangleIdx(0, 11, 5);
    addTriangleIdx(0, 5, 1);
    addTriangleIdx(0, 1, 7);
    addTriangleIdx(0, 7, 10);
    addTriangleIdx(0, 10, 11);

    // 5 adjacent faces
    addTriangleIdx(1, 5, 9);
    addTriangleIdx(5, 11, 4);
    addTriangleIdx(11, 10, 2);
    addTriangleIdx(10, 7, 6);
    addTriangleIdx(7, 1, 8);

    // 5 faces around point 3
    addTriangleIdx(3, 9, 4);
    addTriangleIdx(3, 4, 2);
    addTriangleIdx(3, 2, 6);
    addTriangleIdx(3, 6, 8);
    addTriangleIdx(3, 8, 9);

    // 5 adjacent faces
    addTriangleIdx(4, 9, 5);
    addTriangleIdx(2, 4, 11);
    addTriangleIdx(6, 2, 10);
    addTriangleIdx(8, 6, 7);
    addTriangleIdx(9, 8, 1);
}

void Sphere::addTriangleIdx(Index v1, Index v2, Index v3)
{
    mIndices->push_back(v1);
    mIndices->push_back(v2);
    mIndices->push_back(v3);
}

uint32_t Sphere::getMiddlePoint(uint32_t p1, uint32_t p2)
{
    auto v1 = mVertices->at(p1);
    auto v2 = mVertices->at(p2);
    auto v3 = glm::normalize(glm::vec3(v1.v0) + glm::vec3(v2.v0));
    mVertices->push_back(Vertex3{Position{v3}, mColor});
    return static_cast<uint32_t>(mVertices->size() - 1);
}
