#ifndef MAINOPENGLWIDGET_H
#define MAINOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <gl/GLU.h>

class MainOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MainOpenGLWidget(QWidget *parent = nullptr);
    ~MainOpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MAINOPENGLWIDGET_H
