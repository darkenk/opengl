#include <gtest/gtest.h>

#include "eglfixture.hpp"
#include <shaderprogram.hpp>
#include <units/vertex.hpp>

class ShaderTest : public EGLFixture {
public:
    const std::string frag =
            "#version 330\n"
            "out vec4 out_Color;\n"
            "in vec4 inColor;\n"
            "in vec4 vPosition;\n"
            "void main(void) {\n"
            "   out_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
            "}\n";

    const std::string badfrag =
            "#version 330\n"
            "out vec4 out_Color;\n"
            "in vec4 inColor;\n"
            "in vec4 vPosition;\n"
            "void main(void) {\n"
            "   out_Color = 9vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
            "}\n";
};


TEST_F(ShaderTest, shader_is_correctly_compiled) {
    ShaderProgram sh;
    FragmentShader fs(frag);
    sh.init<Color>(fs);
    EXPECT_EQ(GL_NO_ERROR, glGetError());
}

TEST_F(ShaderTest, attribute_has_correct_location) {
    ShaderProgram sh;
    sh.init<Color>(FragmentShader(frag));
    EXPECT_EQ(GL_NO_ERROR, glGetError());
    sh.activate();
    EXPECT_EQ(GL_NO_ERROR, glGetError());
}

TEST_F(ShaderTest, exception_is_thrown_in_case_of_wrong_shader) {
    ShaderProgram sh;
    EXPECT_ANY_THROW(sh.init<Color>(FragmentShader(badfrag)));
}
