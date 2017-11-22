#include <glad/glad.h>
#include "glwidget.hpp"

#include <memory>
#include <string>
#include <iostream>
#include "utils/exceptions.hpp"
#include <sstream>

void preGLCall(const char* name, void* funcptr, int, ...);
void postGLCall(const char* name, void* funcptr, int, ...);
void checkError(const std::string& func);

GLWidget::~GLWidget() {

}

GLWidget::GLWidget(QWidget* _parent): QGLWidget(_parent, nullptr, Qt::Widget) {
    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    this->setFormat(glFormat);
}

void GLWidget::initializeGL() {
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw GLException("Cannot load glad");
    }
    glad_set_post_callback(postGLCall);

    std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    GLint max_attribs;
    glGetIntegerv (GL_MAX_VERTEX_ATTRIBS, &max_attribs);
    std::cout << max_attribs << std::endl;
}

void GLWidget::resizeGL(int _width, int _height) {
    glViewport(0, 0, _width, _height);
}

void checkError(const std::string& func) {
    GLenum error = glGetError();
    if (error == GL_NO_ERROR) {
        return;
    }
    std::stringstream errorhex;
    errorhex << "0x" << std::hex << error;
    std::string msg = func;
    msg.append(" ");
    msg.append(errorhex.str());
    //        msg.append(reinterpret_cast<const char*>(/*gluErrorString*/(error)));
    throw GLException(msg);
}

void preGLCall(const char* name, void*, int len_args, ...) {
    printf("Calling: %s (%d arguments)\n", name, len_args);
}

void postGLCall(const char* name, void* funcptr, int, ...) {
    if (reinterpret_cast<PFNGLGETERRORPROC>(funcptr) == glGetError) {
        return;
    }
    checkError(name);
}
