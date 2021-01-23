#ifndef MAINOPENGLWIDGET_H
#define MAINOPENGLWIDGET_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <qopenglfunctions_3_3_core.h>
#include <gl/GLU.h>

class MainOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    MainOpenGLWidget(QWidget *parent = nullptr);
    ~MainOpenGLWidget();

    //Compiles a vertical and fragment shader, creates a shader program from them, and returns a shader program
    GLuint makeShaderProgram(const QString vertexShaderSourceFilePath, const QString fragmentShaderSourceFilePath);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    char* openglVersionString = nullptr;
};

#endif // MAINOPENGLWIDGET_H
