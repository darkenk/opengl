#include "cubescene.hpp"
#include <string>

CubeScene::CubeScene(std::istream& input) {
    std::string line;
    unsigned long width = 0;
    unsigned long height = 0;
    while(std::getline(input, line)) {
        auto end = line.end();
        auto iter = line.begin();
        unsigned long x = 0;
        while(iter != end) {
            if (*iter == '#') {
                mCubePositions.emplace_back(Position(static_cast<Meter>(x), 0.0_m, static_cast<Meter>(height)));
            }
            x++;
            iter++;
        }
        if (line.length() > width) {
            width = line.length();
        }
        height++;
    }
    auto end = mCubePositions.end();
    auto p = glm::vec4((width - 1) / 2.0f, 0.0f, (height - 1) / 2.0f, 0.0f);
    for(auto iter = mCubePositions.begin(); iter != end; iter++) {
        iter->v0 -= p;
    }
}
