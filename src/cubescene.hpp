#ifndef CUBESCENE_HPP
#define CUBESCENE_HPP

#include <istream>
#include "units/vertex.hpp"

class CubeScene {
public:
    CubeScene(std::istream& input);

    std::vector<Vertex<Position>>& getCubePositions() {
        return mCubePositions;
    }
private:
    std::vector<Vertex<Position>> mCubePositions;
};

#endif // CUBESCENE_HPP
