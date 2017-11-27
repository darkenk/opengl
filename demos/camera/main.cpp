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
#include "camera.hpp"
#include <glm/glm.hpp>
#include <uniform.hpp>

using namespace std;

static const char* frag =
R"(#version 330 core
    in vec4 vColor;
    out vec4 outColor;
    void main(void) {
        outColor = vColor;
    })";

static const char* vert =
R"(#version 330 core
    in vec4 inColor;
    in vec4 inPosition;
    uniform mat4 mvp;
    out vec4 vColor;
    void main(void) {
        vColor = inColor;
        gl_Position = mvp * inPosition;
    })";

class CameraWidget : public GLWidget {
protected:
    using Vert1 = Vertex<Color, Position>;
    virtual void initializeGL() {
        GLWidget::initializeGL();

        mShaderProgram = make_unique<ShaderProgram>();
        mShaderProgram->init<Color, Position>(FragmentShader(frag), VertexShader(vert));

        auto mVert = make_shared<std::vector<Vert1>>(initializer_list<Vert1>{
             Vert1{Color{1.0, 0.0, 0.0}, Position{-1.0_m, -1.0_m, 0.0_m}},
             Vert1{Color{1.0, 0.0, 0.0}, Position{0.0_m, 1.0_m, 0.0_m}},
             Vert1{Color{1.0, 0.0, 0.0}, Position{1.0_m, -1.0_m, 0.0_m}}});
        mBuffer = make_unique<Buff>(*mVert);
        mCamera = make_unique<Camera>(glm::vec3(0.0f, 0.0f, 1.0f));
    }

    virtual void paintGL() {
        mMVP = mProjectionMatrix * mCamera->getMatrix();
        glClearColor(1.0f, 0.76f, 0.79f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mShaderProgram->activate();
        mShaderProgram->set(mMVP);
        mBuffer->activate();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(3));
        update();
    }

    virtual void resizeGL(int _width, int _height) {
        GLWidget::resizeGL(_width, _height);
        mProjectionMatrix = glm::perspective(
            PI.operator float()/2.0f, // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
            static_cast<float>(_width) / static_cast<float>(_height),       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
            0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
            100.0f             // Far clipping plane. Keep as little as possible.
        );
    }

private:
    unique_ptr<ShaderProgram> mShaderProgram;
    unique_ptr<Camera> mCamera;
    unique_ptr<Buff> mBuffer;
    glm::mat4 mProjectionMatrix;
    UniformMVP mMVP;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CameraWidget widget;
    widget.show();
    return app.exec();
}
