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

static const char* frag =  "#version 330 core\n"
                    "in vec4 vColor;\n"
                    "out vec4 outColor;\n"
                    "void main(void) {\n"
                    "    outColor = vColor;\n"
                    "}\n";

static const char* vert =  "#version 330 core\n"
                    "layout (location = 6 ) in vec4 inColor;\n"
                    "layout (location = 1 ) in vec4 inPosition;\n"
                    "out vec4 vColor;\n"
                    "void main(void) {\n"
                    "    vColor = inColor;\n"
                    "    gl_Position = inPosition;\n"
                    "}\n";


class TriangleWidget : public GLWidget {
protected:
    using Vert1 = Vertex<Color, Position>;
    using Vert2 = std::tuple<Position>;
    virtual void initializeGL() {
        GLWidget::initializeGL();
        Vert1 v;

        mShaderProgram = make_unique<ShaderProgram>();
        mShaderProgram->init<Color, Position>(FragmentShader(frag), VertexShader(vert));
        auto mVert = make_shared<std::vector<Vert1>>(initializer_list<Vert1>{
             Vert1{Color{1.0, 0.0, 0.0}, Position{-1.0_m, -1.0_m, 0.0_m}},
             Vert1{Color{1.0, 0.0, 0.0}, Position{0.0_m, 1.0_m, 0.0_m}},
             Vert1{Color{1.0, 0.0, 0.0}, Position{1.0_m, -1.0_m, 0.0_m}}});
        mBuffer = make_unique<Buff>(*mVert);
    }

    virtual void paintGL() {
        glClearColor(1.0f, 0.76f, 0.79f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mShaderProgram->activate();
        mBuffer->activate();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(3));
//        update();
    }

private:
    unique_ptr<ShaderProgram> mShaderProgram;
    unique_ptr<Buff> mBuffer;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TriangleWidget widget;
    widget.show();
    return app.exec();
}
