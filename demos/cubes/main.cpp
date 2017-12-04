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
#include "uniform.hpp"
#include "camera.hpp"
#include <QKeyEvent>
#include "glm/ext.hpp"
#include "cubescene.hpp"
#include <sstream>

using namespace std;

static const char* vert =
R"(#version 330 core
    in vec4 inPosition;
    out vec4 vColor;
    void main(void) {
        vColor = vec4(0.0, 1.0, 0.0, 0.0);
        gl_Position = inPosition;
    })";

static const char* geom =
R"(#version 330 core
    layout(points) in;
    layout(triangle_strip, max_vertices = 14) out;
    in vec4 vColor[];
    out vec4 fColor;
    uniform mat4 mvp;
    uniform vec4 cu1be[14];
    void main() {
        fColor = vColor[0];
        int i = 0;
        for (i = 0; i < cu1be.length; i++) {
            gl_Position = gl_in[0].gl_Position + cu1be[i];
            gl_Position = mvp * gl_Position;
            EmitVertex();
        }
        EndPrimitive();
    })";

static const char* frag =
R"(#version 330 core
    in vec4 fColor;
    out vec4 outColor;
    void main(void) {
        outColor = fColor;
    })";

static const char* scene =
R"(
######
## ##
#
###
#)";

class Cubes : public GLWidget {
protected:
    using Vert1 = Vertex<Position>;
    virtual void initializeGL() {
        GLWidget::initializeGL();
        mShaderProgram = make_unique<ShaderProgram>();
        mShaderProgram->init<Color, Position>(FragmentShader(frag), VertexShader(vert), GeometryShader(geom));
        std::stringstream stream (scene);
        mCubeScene = make_unique<CubeScene>(stream);
        mBuffer = make_unique<Buff>(mCubeScene->getCubePositions());
        mCamera = make_unique<Camera>(glm::vec3(0.0f, 0.0f, 1.0f));
        mShaderProgram->activate();
        mShaderProgram->set(mMVP);
        mShaderProgram->set(mCube);
        mBuffer->activate();
    }

    virtual void paintGL() {
        mMVP = mProjectionMatrix * mCamera->getMatrix();
        glClearColor(1.0f, 0.76f, 0.79f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mShaderProgram->set(mMVP);
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(mCubeScene->getCubePositions().size()));
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

    virtual void keyPressEvent(QKeyEvent* e) {
        switch (e->key()) {
            case Qt::Key_A:
                mCamera->left();
            break;
            case Qt::Key_D:
                mCamera->right();
            break;
            case Qt::Key_S:
                mCamera->backward();
            break;
            case Qt::Key_W:
                mCamera->forward();
                break;
        }
        e->accept();
        QWidget::keyPressEvent(e);
        update();
    }


private:
    unique_ptr<ShaderProgram> mShaderProgram;
    unique_ptr<Buff> mBuffer;
    unique_ptr<Camera> mCamera;
    glm::mat4 mProjectionMatrix;
    UniformMVP mMVP;
    UniformCUBE mCube;
    unique_ptr<CubeScene> mCubeScene;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Cubes widget;
    widget.show();
    return app.exec();
}
