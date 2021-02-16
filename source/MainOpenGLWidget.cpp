#include "MainOpenGLWidget.h"
#include "globalvars.h"

MainOpenGLWidget::MainOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    sceneManager = new SceneManager;
    //To accept keyboard events
    setFocusPolicy(Qt::StrongFocus);

}

MainOpenGLWidget::~MainOpenGLWidget()
{
    sceneManager->final();
    delete sceneManager;
}

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
    sceneManager->callResizeSceneWindow(w, h);
}

void MainOpenGLWidget::paintGL()
{
    sceneManager->callInitSceneAndOptionsWidgets(this->width(), this->height());
    QElapsedTimer framerateTime;
    framerateTime.start();
    sceneManager->callDrawScene();
    int timeElapsedInMilliseconds = framerateTime.elapsed();
    globalMainWindowFormUI->sceneFramerateLabelMilliseconds->setText(QString::number(timeElapsedInMilliseconds));
    update();
}

void MainOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    sceneManager->callMousePressEventHandler(event);
}

void MainOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    sceneManager->callMouseReleaseEventHandler(event);
}

void MainOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    //"Note that the returned value(event::button()) is always Qt::NoButton for mouse move events."
    sceneManager->callMouseMoveEventHandler(event);
}

void MainOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    sceneManager->callKeyPressEventHandler(event);
}

void MainOpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    sceneManager->callKeyReleaseEventHandler(event);
}
