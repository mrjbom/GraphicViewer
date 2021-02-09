#pragma once
#include <vector>
#include <string>
#include <QOpenGLContext>

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

    virtual void initScene();
    virtual void drawScene();
    virtual void finishScene();

    //There is a management of widgets that allow you to customize the scene
    virtual void createUiOptionsWidgets();
    virtual void deleteUiOptionsWidgets();

    void callInitSceneAndOptionsWidgets();
    void callDrawScene();

public slots:
    void comboBoxChangedCurrentIndex(int newIndex);
};

