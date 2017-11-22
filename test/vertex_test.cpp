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
