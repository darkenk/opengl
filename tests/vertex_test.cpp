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
#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "units/vertex.hpp"

using namespace std;

class Position2D : public glm::vec2
{
public:
    explicit Position2D() {}
};

TEST(VertexTest, vertex_size)
{
    Vertex<Position> v;
    EXPECT_ANY_THROW(v.getOffset(1));
    EXPECT_EQ(0, v.getOffset(0));
    EXPECT_EQ(sizeof(Position), sizeof(v));
    using Vertex2 = Vertex<Position, Position2D>;
    Vertex2 v2;
    EXPECT_EQ(sizeof(Position) + sizeof(Position2D), sizeof(v2));
    EXPECT_EQ(0, v2.getOffset(0));
    EXPECT_EQ(sizeof(Position), v2.getOffset(1));

    using Vertex4 = Vertex<Position, Position, Position>;
    Vertex4 v3;
    EXPECT_EQ(0, v3.getOffset(0));
    EXPECT_EQ(sizeof(Position), v3.getOffset(1));
    EXPECT_EQ(sizeof(Position) + sizeof(Position), v3.getOffset(2));
}

TEST(VertexTest, default_constructor)
{
    {
        Vertex<Position> v{Position(1.0_m, 0.0_m, 1.0_m)};
        EXPECT_EQ(v.v0.x, 1.0f);
        EXPECT_EQ(v.v0.y, 0.0f);
        EXPECT_EQ(v.v0.z, 1.0f);
    }
    Vertex<Position, Position2D> v{Position(1.0_m, 0.0_m, 1.0_m)};
}
