#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <array>

class UniformMVP {
public:
    template<typename T>
    UniformMVP& operator=(const T t) {
        matrix = t;
        return *this;
    }

    operator glm::mat4() const {
        return matrix;
    }

    void setGL(GLint location) const {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::string name() const {
        static constexpr const char* n = "mvp";
        return std::string(n);
    }

private:
    glm::mat4 matrix;
};


class UniformCUBE {
public:
    UniformCUBE() {
        vertices = {{
            glm::vec4(-1.f, 1.f, 1.f, 0.f),     // Front-top-left
            glm::vec4(1.f, 1.f, 1.f, 0.f), // Front-top-right
            glm::vec4(-1.f, -1.f, 1.f, 0.f),   // Front-bottom-left
            glm::vec4(1.f, -1.f, 1.f, 0.f),    // Front-bottom-right
            glm::vec4(1.f, -1.f, -1.f, 0.f),   // Back-bottom-right
            glm::vec4(1.f, 1.f, 1.f, 0.f),     // Front-top-right
            glm::vec4(1.f, 1.f, -1.f, 0.f),    // Back-top-right
            glm::vec4(-1.f, 1.f, 1.f, 0.f),    // Front-top-left
            glm::vec4(-1.f, 1.f, -1.f, 0.f),   // Back-top-left
            glm::vec4(-1.f, -1.f, 1.f, 0.f),   // Front-bottom-left
            glm::vec4(-1.f, -1.f, -1.f, 0.f),  // Back-bottom-left
            glm::vec4(1.f, -1.f, -1.f, 0.f),    // Back-bottom-right
            glm::vec4(-1.f, 1.f, -1.f, 0.f),    // Back-top-left
            glm::vec4(1.f, 1.f, -1.f, 0.f)      // Back-top-right
        }};
    }

    glm::vec4& operator[](unsigned int idx) {
        return vertices[idx];
    }

    void setGL(GLint location) const {
        glUniform4fv(location, 14, glm::value_ptr(vertices[0]));
    }

    std::string name() const {
        static constexpr const char* n = "cu1be[0]";
        return std::string(n);
    }

private:
    std::array<glm::vec4, 14> vertices;

};

#endif // UNIFORM_HPP
