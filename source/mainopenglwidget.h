#ifndef MAINOPENGLWIDGET_H
#define MAINOPENGLWIDGET_H

#include <QDebug>
#include <QTime>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <GL/GLU.h>
#include "SceneManager/SceneManager.h"
#include "ShaderProgram.h"

class MainOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    MainOpenGLWidget(QWidget *parent = nullptr);
    ~MainOpenGLWidget();
    SceneManager* sceneManager = nullptr;
    char* openglVersionString = nullptr;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MAINOPENGLWIDGET_H
