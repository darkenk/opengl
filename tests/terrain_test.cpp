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
#include <gtest/gtest.h>
#include "../src/models/terrain.hpp"
#include "../src/models/heightmap.hpp"
#include <gmock/gmock.h>
#include <array>

using namespace std;

using testing::ElementsAre;

template<class T, size_t size>
::testing::AssertionResult VertexMatch(const array<T, size> expected,
                                       const vector<Vertex3> actual,
                                       function<bool(const T&, const Vertex3&)> compare)
{
    for (size_t i(0); i < size; ++i){
        if (compare(expected[i], actual[i])) {
            return ::testing::AssertionFailure() << "array[" << i
                << "] (" << actual[i].v2 << ") != expected[" << i
                << "] (" << expected[i] << ")";
        }
    }
    return ::testing::AssertionSuccess();
}

template<size_t size>
::testing::AssertionResult NormalsMatch(const array<Vector, size> expected,
                                        const vector<Vertex3> actual)
{
    auto normalsCompare = [](const Vector& normal, const Vertex3& vertex) -> bool {
        auto v = normal - vertex.v2;
        for (int i = 0; i < 3; i++) {
            if (abs(v[i]) > 0.001f) {
                return true;
            }
        }
        return false; };
    return VertexMatch<Vector>(expected, actual, normalsCompare);
}

template<size_t size>
::testing::AssertionResult HeightMatch(const array<float, size> expected,
                                        const vector<Vertex3> actual)
{
    auto compare = [](const float& height, const Vertex3& vertex) -> bool {
        return abs(height - vertex.v0.y) > 0.001f; };
    return VertexMatch<float>(expected, actual, compare);
}

class HeightMap2x2: public HeightMap
{
public:
    HeightMap2x2() : HeightMap(2, 2) {
        mHeightMap[0][0] = 1.0f;
        mHeightMap[0][1] = 2.0f;
        mHeightMap[1][0] = 3.0f;
        mHeightMap[1][1] = 4.0f;
    }
};

TEST(TerrainTest, generate_terrain_2x2)
{
    Terrain t(HeightMap2x2{});
    EXPECT_EQ(4, t.getVertices()->size());
    EXPECT_EQ(6, t.getIndices()->size());
    ASSERT_THAT(*t.getIndices(), ElementsAre(3, 1, 0, 2, 3, 0));
    array<float, 4> expected { { 1.0f, 2.0f, 3.0f, 4.0f} };
    EXPECT_TRUE(HeightMatch(expected, *t.getVertices()));
}

class HalfFlatMap: public HeightMap
{
public:
    HalfFlatMap(uint32_t w, uint32_t h) : HeightMap(w, h) {
        for (uint32_t i = 0; i < w; i++) {
            for (uint32_t j = 0; j < h; j++) {
                mHeightMap[i][j] = 0.5f;
            }
        }
    }
};

TEST(TerrainTest, computing_normals_for_flat_height_map)
{
    array<Vector, 4> expected{ {Vector{0.0f, 1.0f, 0.0f}, Vector{0.0f, 1.0f, 0.0f},
            Vector{0.0f, 1.0f, 0.0f}, Vector{0.0f, 1.0f, 0.0f}} };
    {
        Terrain t(HeightMap(2, 2));
        EXPECT_TRUE(NormalsMatch(expected, *t.getVertices()));
    }
    {
        Terrain t(HalfFlatMap(2, 2));
        EXPECT_TRUE(NormalsMatch(expected, *t.getVertices()));
    }
}

TEST(TerrainTest, computing_normals_for_map_2x2)
{
    auto a = glm::vec3(0.0f, 1.0f, 0.0f);
    auto b = glm::vec3(1.0f, 2.0f, 0.0f);
    auto c = glm::vec3(0.0f, 3.0f, 1.0f);
    auto d = glm::vec3(1.0f, 4.0f, 1.0f);
    auto f1 = glm::normalize(glm::cross(a - b, d - b));
    auto f2 = glm::normalize(glm::cross(a - d, c - d));
    array<Vector, 4> expected{ {Vector{(f1+f2)/2.f}, Vector{f1},
            Vector{f2}, Vector{(f1+f2)/2.f}} };
    Terrain t(HeightMap2x2{});
    EXPECT_TRUE(NormalsMatch(expected, *t.getVertices()));
}

class HeightMap2x3: public HeightMap
{
public:
    HeightMap2x3() : HeightMap(2, 3) {
        mHeightMap[0][0] = 1.0f;
        mHeightMap[0][1] = 2.0f;
        mHeightMap[1][0] = 3.0f;
        mHeightMap[1][1] = 4.0f;
        mHeightMap[2][0] = 1.0f;
        mHeightMap[2][1] = 2.0f;
    }
};

TEST(TerrainTest, computing_normals_for_map_2x3)
{
    auto a = glm::vec3(0.0f, 1.0f, 0.0f);
    auto b = glm::vec3(1.0f, 2.0f, 0.0f);
    auto c = glm::vec3(0.0f, 3.0f, 1.0f);
    auto d = glm::vec3(1.0f, 4.0f, 1.0f);
    auto e = glm::vec3(0.0f, 1.0f, 2.0f);
    auto f = glm::vec3(1.0f, 2.0f, 2.0f);

    auto f1 = glm::normalize(glm::cross(a - b, d - b));
    auto f2 = glm::normalize(glm::cross(a - d, c - d));
    auto f3 = glm::normalize(glm::cross(c - d, f - d));
    auto f4 = glm::normalize(glm::cross(c - f, e - f));

    array<Vector, 6> expected{ {Vector{glm::normalize((f1+f2)/2.f)}, Vector{f1},
            Vector{glm::normalize((f2+f3+f4)/3.0f)}, Vector{glm::normalize((f1+f2+f3)/3.0f)},
            Vector{f4}, Vector{glm::normalize((f3+f4)/2.0f)}} };
    Terrain t(HeightMap2x3{});
    EXPECT_TRUE(NormalsMatch(expected, *t.getVertices()));
}

class HeightMap3x3: public HeightMap
{
public:
    HeightMap3x3() : HeightMap(3, 3) {
        mHeightMap[0][0] = 1.0f;
        mHeightMap[0][1] = 2.0f;
        mHeightMap[0][2] = 3.0f;
        mHeightMap[1][0] = 4.0f;
        mHeightMap[1][1] = 5.0f;
        mHeightMap[1][2] = 5.0f;
        mHeightMap[2][0] = 1.0f;
        mHeightMap[2][1] = 2.0f;
        mHeightMap[2][2] = 3.0f;
    }
};

TEST(TerrainTest, computing_normals_for_map_3x3)
{
    auto a = glm::vec3(0.0f, 1.0f, 0.0f);
    auto b = glm::vec3(1.0f, 2.0f, 0.0f);
    auto c = glm::vec3(2.0f, 3.0f, 0.0f);
    auto d = glm::vec3(0.0f, 4.0f, 1.0f);
    auto e = glm::vec3(1.0f, 5.0f, 1.0f);
    auto f = glm::vec3(2.0f, 5.0f, 1.0f);
    auto g = glm::vec3(0.0f, 1.0f, 2.0f);
    auto h = glm::vec3(1.0f, 2.0f, 2.0f);
    auto i = glm::vec3(2.0f, 3.0f, 2.0f);

    auto f1 = glm::normalize(glm::cross(a - b, e - b));
    auto f2 = glm::normalize(glm::cross(a - e, d - e));
    auto f3 = glm::normalize(glm::cross(b - c, f - c));
    auto f4 = glm::normalize(glm::cross(b - f, e - f));
    auto f5 = glm::normalize(glm::cross(d - e, h - e));
    auto f6 = glm::normalize(glm::cross(d - h, g - h));
    auto f7 = glm::normalize(glm::cross(e - f, i - f));
    auto f8 = glm::normalize(glm::cross(e - i, h - i));

    array<Vector, 9> expected{ {Vector{glm::normalize(f1+f2)}, Vector{glm::normalize(f1+f4+f3)},
            Vector{glm::normalize(f3)}, Vector{glm::normalize(f2+f5+f6)},
            Vector{glm::normalize(f1+f4+f7+f8+f5+f2)}, Vector{glm::normalize(f3+f4+f7)},
            Vector{glm::normalize(f6)}, Vector{glm::normalize(f6+f5+f8)}, Vector{glm::normalize(f8+f7)}} };
    Terrain t(HeightMap3x3{});
    EXPECT_TRUE(NormalsMatch(expected, *t.getVertices()));
}
