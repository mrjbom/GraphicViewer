#include "MainOpenGLWidget.h"
#include "globalvars.h"
#include <QFile>

MainOpenGLWidget::MainOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    sceneManager = new SceneManager;

}

MainOpenGLWidget::~MainOpenGLWidget()
{
    sceneManager->final();
    delete sceneManager;
}

//The vertices are specified in counter-clockwise order
// A
// |\
// | \
// |  \
// B---C
// A->B->C
//float vertexes_coords_normalized[] =
//                     { 0, 0.5, 0,
//                       -0.5, -0.5, 0,
//                       0.5, -0.5, 0 };

unsigned int gVAO = 0;
unsigned int gShaderProgram = 0;

void MainOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    openglVersionString = (char*)glGetString(GL_VERSION);
    sceneManager->init(this->context());
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, this->width(), this->height());

}

void MainOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MainOpenGLWidget::paintGL()
{
    sceneManager->callInitSceneAndOptionsWidgets();
    QTime framerateTime;
    framerateTime.start();
    sceneManager->callDrawScene();
    int timeElapsedInMilliseconds = framerateTime.elapsed();
    globalMainWindowFormUI->sceneFramerateLabelMilliseconds->setText(QString::number(timeElapsedInMilliseconds));

    update();
}
