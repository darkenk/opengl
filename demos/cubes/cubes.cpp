#include <QApplication>
#include <memory>
#include <string>
#include <iostream>
#include <dk_utils/make_unique.hpp>
#include "units/units.hpp"
#include "buffer.hpp"
#include "shaderprogram.hpp"
#include "utils/exceptions.hpp"
#include "glwidget.hpp"

using namespace std;

static const char* vert =  "#version 330 core\n"
                    "in vec4 inColor;\n"
                    "in vec4 inPosition;\n"
                    "out vec4 vColor;\n"
                    "void main(void) {\n"
                    "    vColor = inColor;\n"
                    "    gl_Position = inPosition;\n"
                    "}\n";

static const char* geom =  "#version 330 core\n"
                           "layout(points) in;\n"
                           "layout(triangle_strip, max_vertices = 4) out;\n"
                           "in vec4 vColor[];\n"
                           "out vec4 fColor;\n"
                           "void main()\n"
                           "{\n"
                                "fColor = vColor[0]\n;"
                               "gl_Position = gl_in[0].gl_Position + vec4(-0.25, 0.25, 0.0, 0.0);\n"
                               "EmitVertex();\n"
                               "gl_Position = gl_in[0].gl_Position + vec4(0.25, 0.25, 0.0, 0.0);\n"
                               "EmitVertex();\n"
                                "gl_Position = gl_in[0].gl_Position + vec4(-0.25, -0.25, 0.0, 0.0);\n"
                                "EmitVertex();\n"
                                "gl_Position = gl_in[0].gl_Position + vec4(0.25, -0.25, 0.0, 0.0);\n"
                                "EmitVertex();\n"
                                "EndPrimitive();\n"
                           "}\n";

static const char* frag =  "#version 330 core\n"
                    "in vec4 fColor;\n"
                    "out vec4 outColor;\n"
                    "void main(void) {\n"
                    "    outColor = fColor;\n"
                    "}\n";

class GeomShader : public GLWidget {
protected:
    using Vert1 = Vertex<Color, Position>;
    virtual void initializeGL() {
        GLWidget::initializeGL();
        Vert1 v;
        mShaderProgram = make_unique<ShaderProgram>();
        mShaderProgram->init<Color, Position>(FragmentShader(frag), VertexShader(vert), GeometryShader(geom));
        auto mVert = make_shared<std::vector<Vert1>>(initializer_list<Vert1>{
             Vert1{Color{1.0, 0.0, 0.0}, Position{-0.5_m, -0.5_m, 0.0_m}},
             Vert1{Color{0.0, 1.0, 0.0}, Position{0.0_m, 0.5_m, 0.0_m}},
             Vert1{Color{0.0, 0.0, 1.0}, Position{0.5_m, -0.5_m, 0.0_m}}});
        mBuffer = make_unique<Buff>(*mVert);
    }

    virtual void paintGL() {
        glClearColor(1.0f, 0.76f, 0.79f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mShaderProgram->activate();
        mBuffer->activate();
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(3));
    }

private:
    unique_ptr<ShaderProgram> mShaderProgram;
    unique_ptr<Buff> mBuffer;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GeomShader widget;
    widget.show();
    return app.exec();
}
