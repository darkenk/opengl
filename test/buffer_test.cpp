#include <gtest/gtest.h>
#include "eglfixture.hpp"
#include "buffer.hpp"
#include "shaderprogram.hpp"
#include "units/units.hpp"
#include "units/vertex.hpp"

class BufferTest : public EGLFixture {
protected:
    const std::string frag =
            "#version 330\n"
            "out vec4 out_Color;\n"
            "in vec3 inTestAttrib;\n"
            "in vec4 vPosition;\n"
            "void main(void) {\n"
            "   out_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
            "}\n";
};

using Vert2 = Vertex<Position, Color>;

class TestAttrib : public glm::vec4 {
public:
    static constexpr GLuint location = 4;
    static constexpr GLenum type = GL_FLOAT;
    static constexpr GLint size = 3;
    static constexpr const char* name = "inTestAttrib";
};

TEST_F(BufferTest, attributes_are_set_correctly) {
    std::vector<Vertex<TestAttrib>> data;
    Buff b(data);
    b.activate();
    GLint size = TestAttrib::size;
    GLenum type = TestAttrib::type;
    GLint ret;
    glGetVertexAttribIiv(TestAttrib::location, GL_VERTEX_ATTRIB_ARRAY_SIZE, &ret);
    EXPECT_EQ(GL_NO_ERROR, glGetError());
    EXPECT_EQ(size, ret);
    glGetVertexAttribIiv(TestAttrib::location, GL_VERTEX_ATTRIB_ARRAY_TYPE, &ret);
    EXPECT_EQ(GL_NO_ERROR, glGetError());
    EXPECT_EQ(type, ret);
    glGetVertexAttribIiv(TestAttrib::location, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &ret);
    EXPECT_EQ(GL_NO_ERROR, glGetError());
    EXPECT_EQ(sizeof(TestAttrib), ret);
};
