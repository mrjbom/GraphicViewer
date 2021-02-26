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

//void MainOpenGLWidget::mousePressEvent(QMouseEvent* event)
//{
//    sceneManager->callMousePressEventHandler(*event);
//}
//
//void MainOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
//{
//    sceneManager->callMouseReleaseEventHandler(*event);
//}
//
//void MainOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
//{
//    //"Note that the returned value(event::button()) is always Qt::NoButton for mouse move events."
//
//    sceneManager->callMouseMoveEventHandler(*event);
//}

void MainOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    //mouseCaptured = true;
    //virtualMousePosition = this->rect().center();
    //setCursor(Qt::BlankCursor);
    //QCursor::setPos(mapToGlobal(this->rect().center()));
    //QMouseEvent eventCopy(event->type(), virtualMousePosition, event->button(), event->buttons(), event->modifiers());
    //sceneManager->callMousePressEventHandler(eventCopy);
    ////QWidget::mousePressEvent(event);

    QMouseEvent eventCopy = *event;
    sceneManager->callMousePressEventHandler(eventCopy);
}

void MainOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    //QCursor::setPos(mapToGlobal(virtualMousePosition));
    //setCursor(Qt::ArrowCursor);
    //QMouseEvent eventCopy(event->type(), virtualMousePosition, event->button(), event->buttons(), event->modifiers());
    //sceneManager->callMouseReleaseEventHandler(eventCopy);
    ////QWidget::mouseReleaseEvent(event);

    QMouseEvent eventCopy = *event;
    sceneManager->callMouseReleaseEventHandler(eventCopy);
}

void MainOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    //"Note that the returned value(event::button()) is always Qt::NoButton for mouse move events."

    //if (event->buttons() & Qt::LeftButton)
    //{
    //    //The area where the real mouse cursor should be located to configure the virtual
    //    //mouse (otherwise, due to the specifics of WinAPI, sharp jerks of the virtual mouse cursor are possible)
    //    QRect controlRectangle(rect().center().x() - CONTROL_AREA_RECTANGLE_LEFT_X_OFFSET, rect().center().y() - CONTROL_AREA_RECTANGLE_LEFT_Y_OFFSET, CONTROL_AREA_RECTANGLE_X_SIZE, CONTROL_AREA_RECTANGLE_Y_SIZE);
    //    if(controlRectangle.contains(event->pos())) {
    //        virtualMousePosition += (event->pos() - rect().center());
    //        QMouseEvent eventCopy(event->type(), virtualMousePosition, event->button(), event->buttons(), event->modifiers());
    //        sceneManager->callMouseMoveEventHandler(eventCopy);
    //        //QCursor::setPos(mapToGlobal(this->rect().center()));
    //    }
    //    QCursor::setPos(mapToGlobal(this->rect().center()));
    //}
    ////QWidget::mouseMoveEvent(event);

    QMouseEvent eventCopy = *event;
    sceneManager->callMouseMoveEventHandler(eventCopy);


}

void MainOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    sceneManager->callKeyPressEventHandler(event);
}

void MainOpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    sceneManager->callKeyReleaseEventHandler(event);
}
