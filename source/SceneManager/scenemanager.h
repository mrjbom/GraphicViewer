#pragma once
#include <vector>
#include <string>
#include <QOpenGLContext>
#include <QMouseEvent>
#include <QKeyEvent>

class SceneManager : public QObject
{
    Q_OBJECT
private:
    QOpenGLContext* openGLContext = nullptr;
    std::vector<SceneManager*> sceneObjectsList;
    //Address of the object obtained during memory allocation, saved for the correct memory release
    std::vector<void*> sceneObjectsVoidPtrList;
    std::vector<QString> sceneObjectsNamesList;
    std::vector<bool> sceneObjectsInitStatusList;
    size_t currentObjectIndex = 0;
public:
    SceneManager();
    virtual ~SceneManager();
    void init(QOpenGLContext* openGLContext);
    void final();
    void addSceneObject(SceneManager* newSceneObjectPtr, void* newSceneObjectVoidPtr, const QString sceneName);
    void setCurrentSceneObjectIndex(size_t newCurrentObjectIndex);
    QString getSceneName(size_t index);
    size_t getScenesNumber();

    //Functions to be defined in the child class of the scene
    virtual void initScene(int start_window_width, int start_window_height);
    virtual void drawScene();
    virtual void finishScene();
    //These functions do not need to be declared
    virtual void resizeSceneWindow(int w, int h);
    virtual void mousePressEventHandler(QMouseEvent* event);
    virtual void mouseReleaseEventHandler(QMouseEvent* event);
    virtual void mouseMoveEventHandler(QMouseEvent* event);
    virtual void keyPressEventHandler(QKeyEvent* event);
    virtual void keyReleaseEventHandler(QKeyEvent* event);
    //There is a management of widgets that allow you to customize the scene
    virtual void createUiOptionsWidgets();
    virtual void deleteUiOptionsWidgets();

    void callInitSceneAndOptionsWidgets(int start_window_width, int start_window_height);
    void callDrawScene();
    void callResizeSceneWindow(int w, int h);
    void callMousePressEventHandler(QMouseEvent* event);
    void callMouseReleaseEventHandler(QMouseEvent* event);
    void callMouseMoveEventHandler(QMouseEvent* event);
    void callKeyPressEventHandler(QKeyEvent* event);
    void callKeyReleaseEventHandler(QKeyEvent* event);

public slots:
    void comboBoxChangedCurrentIndex(int newIndex);
};

