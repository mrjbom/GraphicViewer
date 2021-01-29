#include <iostream>
#include "SceneManager.h"
#include "../globalvars.h"
#include "Scenes/Sc1VBOOrange/Sc1VBOOrange.h"
#include "Scenes/Sc2VAOBlue/Sc2VAOBlue.h"
#include <QMetaMethod>

SceneManager::SceneManager()
{
    //YOU CAN'T PLACE CODE HERE
    //You should use the init() function
}

SceneManager::~SceneManager()
{
	//YOU CAN'T PLACE CODE HERE
	//You should use the final() function
}

void SceneManager::init(QOpenGLContext* openGLContext)
{
    this->openGLContext = openGLContext;
    void* scenePtr = nullptr;

    scenePtr = new Sc1VBOOrange(openGLContext);
    addSceneObject((SceneManager*)scenePtr, (void*)scenePtr, "Triangle VBO(Orange)");

    scenePtr = new Sc2VAOBlue(openGLContext);
    addSceneObject((SceneManager*)scenePtr, (void*)scenePtr, "Triangle VAO(Blue)");

    setCurrentSceneObjectIndex(0);

    //Configuring the scene combo-box to select the current scene
    for(size_t i = 0; i < getScenesNumber(); ++i) {
        globalMainWindowFormUI->sceneSelectorComboBox->addItem(getSceneName(i));
    }
    QObject::connect(globalMainWindowFormUI->sceneSelectorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChangedCurrentIndex(int)));
}

void SceneManager::final()
{
	for (size_t i = 0; i < sceneObjectsVoidPtrList.size(); i++) {
        //sceneObjectsList[i]->~SceneManager();
        //prevents calling finishScene() for inactive scenes
        if(i == currentObjectIndex) {
            sceneObjectsList[i]->finishScene();
        }
		delete sceneObjectsVoidPtrList[i];
	}
}

void SceneManager::addSceneObject(SceneManager* newSceneObjectPtr, void* newSceneObjectVoidPtr, const QString sceneName)
{
	sceneObjectsList.push_back(newSceneObjectPtr);
	sceneObjectsVoidPtrList.push_back(newSceneObjectVoidPtr);
	sceneObjectsNamesList.push_back(sceneName);
    sceneObjectsInitStatusList.push_back(false);
}

void SceneManager::setCurrentSceneObjectIndex(size_t newCurrentIndex)
{
	if (currentObjectIndex == newCurrentIndex) {
		return;
	}
    sceneObjectsInitStatusList[currentObjectIndex] = false;
    sceneObjectsList[currentObjectIndex]->finishScene();
	currentObjectIndex = newCurrentIndex;
}

QString SceneManager::getSceneName(size_t index)
{
    return sceneObjectsNamesList[index];
}

size_t SceneManager::getScenesNumber()
{
    return sceneObjectsList.size();
}

void SceneManager::initScene()
{
    //DON'T USE
}

void SceneManager::drawScene()
{
    //DON'T USE
}

void SceneManager::finishScene()
{
    //DON'T USE
}

void SceneManager::callInitScene()
{
	if (sceneObjectsList.size() == 0) {
		return;
	}
	if (sceneObjectsInitStatusList[currentObjectIndex] == false) {
		sceneObjectsInitStatusList[currentObjectIndex] = true;
		sceneObjectsList[currentObjectIndex]->initScene();
		return;
	}
}

void SceneManager::callDrawScene()
{
	if (sceneObjectsList.size() == 0) {
		return;
	}
	sceneObjectsList[currentObjectIndex]->drawScene();
}

void SceneManager::comboBoxChangedCurrentIndex(int newIndex) {
    setCurrentSceneObjectIndex(newIndex);
}
