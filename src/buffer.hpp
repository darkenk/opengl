#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "units/vertex.hpp"
#include <type_traits>

class Buff
{
public:
    template<typename... Elements>
    Buff(const std::vector<Vertex<Elements...>>& data) {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        GLuint elementSize = sizeof(Vertex<Elements...>);
        std::cout << "Buff size " << elementSize * data.size() << std::endl;
        glBufferData(GL_ARRAY_BUFFER, elementSize * data.size(), data.data(), GL_STATIC_DRAW);
        enableVertex<Elements...>(elementSize, 0);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Buff() {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
    }

    void activate() {
        glBindVertexArray(mVAO);
    }

    void deactivate() {
        glBindVertexArray(0);
    }

private:
    GLuint mVAO;
    GLuint mVBO;

    template<typename T, typename std::enable_if<not std::is_empty<T>::value>::type* = nullptr>
    void enableVertex(GLuint stride, GLuint offset) {
        std::cout << " enable: " << T::name << " location " << T::location << " size " << T::size
                  << " stride " << stride << " offset " << offset << std::endl;
        glVertexAttribPointer(T::location, T::size, T::type, GL_FALSE, stride,
                              reinterpret_cast<void*>(offset));
        glEnableVertexAttribArray(T::location);
    }

    template<typename T, typename std::enable_if<std::is_empty<T>::value>::type* = nullptr>
    void enableVertex(GLuint /*stride*/, GLuint /*offset*/) {}

    template<typename T, typename T2, typename... Tp>
    void enableVertex(GLuint stride, GLuint offset) {
        enableVertex<T>(stride, offset);
        enableVertex<T2, Tp...>(stride, offset + sizeof(T));
    }
};

#endif // BUFFER_HPP
