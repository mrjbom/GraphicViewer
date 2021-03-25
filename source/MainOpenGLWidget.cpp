#include "MainOpenGLWidget.h"
#include "globalvars.h"

MainOpenGLWidget::MainOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    sceneManager = new SceneManager;
    //To accept keyboard events
    setFocusPolicy(Qt::StrongFocus);

    glTimeMonitor = new QOpenGLTimeMonitor;

    frametimeLabelUpdateTimer = new QTimer();
    QObject::connect(frametimeLabelUpdateTimer, &QTimer::timeout, this, &MainOpenGLWidget::updateFrameRenderLabel);
    frametimeLabelUpdateTimer->setInterval(200);
    frametimeLabelUpdateTimer->start();

    QObject::connect(this, &MainOpenGLWidget::frameSwapped, this, &MainOpenGLWidget::frameSwappedSlot);
}

MainOpenGLWidget::~MainOpenGLWidget()
{
    sceneManager->final();
    glTimeMonitor->destroy();
    glTimeMonitor->deleteLater();
    delete sceneManager;
    delete frametimeLabelUpdateTimer;
}

void MainOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glTimeMonitor->setSampleCount(2);
    if(!glTimeMonitor->create()) {
        qInfo() << "[ERROR] initializeGL: GL time monitor create() failed!";
        return;
    }
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
    glTimeMonitor->reset();
    glTimeMonitor->recordSample();
    sceneManager->callInitSceneAndOptionsWidget(this->width(), this->height());
    sceneManager->callDrawScene();
    glTimeMonitor->recordSample();
    lastFrameRenderTimeInNanoseconds = glTimeMonitor->waitForIntervals()[0];
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

void MainOpenGLWidget::updateFrameRenderLabel()
{
    double timeElapsedInMilliseconds = lastFrameRenderTimeInNanoseconds / 1000000.0f;
    QString formatedString = "";
    QString frametimeString = QString::number(timeElapsedInMilliseconds);
    QString fpsString = "";
    if(timeElapsedInMilliseconds == 0) {
        timeElapsedInMilliseconds = 0.000001;
    }
    uint64_t fps = 1000.0f / timeElapsedInMilliseconds;
    if(fps > 1000) {
        fpsString = " > 1000";
    }
    else {
        fpsString = QString::number(fps);
    }
    formatedString = frametimeString + " ms (FPS" + fpsString + ")";
    globalMainWindowFormUI->sceneFramerateLabelMilliseconds->setText(formatedString);
}

void MainOpenGLWidget::frameSwappedSlot()
{
    update();
}
