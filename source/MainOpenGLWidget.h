#ifndef MAINOPENGLWIDGET_H
#define MAINOPENGLWIDGET_H

#include <QDebug>
#include <QPoint>
#include <QElapsedTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "SceneManager/SceneManager.h"
#include "ShaderProgram.h"

class MainOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
private:
    //Required offsets to build the area where the mouse shift is checked to update the position of the virtual mouse
    const int CONTROL_AREA_RECTANGLE_LEFT_X_OFFSET = 20;
    const int CONTROL_AREA_RECTANGLE_LEFT_Y_OFFSET = 20;
    const int CONTROL_AREA_RECTANGLE_X_SIZE = 40;
    const int CONTROL_AREA_RECTANGLE_Y_SIZE = 40;

    bool mouseCaptured = false;
    QPoint virtualMousePosition = { 0, 0 };
    QPoint mouseLastPositon = { 0, 0 };
    QString savedWindowTitle = "";
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
