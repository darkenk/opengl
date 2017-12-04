#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

#include <cubescene.hpp>

using ::testing::ContainerEq;

TEST(CubeSceneTest, one_cube_is_in_center) {
    std::stringstream in("#");
    CubeScene cs(in);
    std::vector<Vertex<Position>> expect{{Position(0.0_m, 0.0_m, 0.0_m)}};
    EXPECT_THAT(cs.getCubePositions(), ContainerEq(expect));
}

TEST(CubeSceneTest, two_cubes_in_a_row_are_in_center) {
    std::stringstream in("##");
    CubeScene cs(in);
    std::vector<Vertex<Position>> expect{{Position(-0.5_m, 0.0_m, 0.0_m), Position(0.5_m, 0.0_m, 0.0_m)}};
    EXPECT_THAT(cs.getCubePositions(), ContainerEq(expect));
}

TEST(CubeSceneTest, two_cubes_in_a_colum_are_in_center) {
    std::stringstream in("#\n#");
    CubeScene cs(in);
    std::vector<Vertex<Position>> expect{{Position(0.0_m, 0.0_m, -0.5_m), Position(0.0_m, 0.0_m, 0.5_m)}};
    EXPECT_THAT(cs.getCubePositions(), ContainerEq(expect));
}

TEST(CubeSceneTest, cubes_are_centered_in_both_directions) {
    std::stringstream in("# #\n #");
    CubeScene cs(in);
    std::vector<Vertex<Position>> expect{{Position(-1.0_m, 0.0_m, -0.5_m), Position(1.0_m, 0.0_m, -0.5_m),
                                 Position(0.0_m, 0.0_m, 0.5_m)}};
    EXPECT_THAT(cs.getCubePositions(), ContainerEq(expect));
}
