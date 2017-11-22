#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QWidget>
#include <QGLWidget>

class GLWidget : public QGLWidget {
public:
    GLWidget(QWidget* _parent = nullptr);

    virtual ~GLWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int _width, int _height);

};

#endif // GLWIDGET_HPP
