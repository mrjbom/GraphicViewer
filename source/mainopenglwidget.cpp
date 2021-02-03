#include "mainopenglwidget.h"
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-this->width() / 2, this->width() / 2, -this->height() / 2, this->height() / 2);
    glViewport(0, 0, this->width(), this->height());

}

void MainOpenGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    glViewport(0, 0, w, h);
}

void MainOpenGLWidget::paintGL()
{
    sceneManager->callInitScene();
    sceneManager->callDrawScene();
    update();
}
