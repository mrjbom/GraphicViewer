#ifndef MAINOPENGLWIDGET_H
#define MAINOPENGLWIDGET_H

#include <QDebug>
#include <QElapsedTimer>
#include <QEvent>
#include <QMouseEvent>
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
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};

#endif // MAINOPENGLWIDGET_H
