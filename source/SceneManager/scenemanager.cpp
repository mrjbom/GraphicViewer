#include <iostream>
#include "SceneManager.h"
#include "../globalvars.h"
#include "Scenes/Sc0Test/Sc0Test.h"
#include "Scenes/Sc1VBOOrange/Sc1VBOOrange.h"
#include "Scenes/Sc2VAOBlue/Sc2VAOBlue.h"
#include "Scenes/Sc3EBOGreen/Sc3EBOGreen.h"
#include "Scenes/Sc4UniformInput/Sc4UniformInput.h"
#include "Scenes/Sc5Texture/Sc5Texture.h"
#include "Scenes/Sc6Box3DPerspective/Sc6Box3DPerspective.h"
#include "Scenes/Sc7Box3DCam/Sc7Box3DCam.h"
#include "Scenes/Sc8Lighting/Sc8Lighting.h"
#include "Scenes/Sc9LightingMaps/Sc9LightingMaps.h"
#include "Scenes/Sc10ManyCubesLM/Sc10ManyCubesLM.h"

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
    //Save OpenGL context
    this->openGLContext = openGLContext;
    SceneManager* scenePtr = nullptr;

    //scenePtr = new Sc0Test(openGLContext);
    //addSceneObject(scenePtr, "Test scene");
    //
    //scenePtr = new Sc1VBOOrange(openGLContext);
    //addSceneObject(scenePtr, "Triangle VBO(Orange)");
    //
    //scenePtr = new Sc2VAOBlue(openGLContext);
    //addSceneObject(scenePtr, "Triangle VAO(Blue)");
    //
    //scenePtr = new Sc3EBOGreen(openGLContext);
    //addSceneObject(scenePtr, "Triangle EBO(Green)");
    //
    //scenePtr = new Sc4UniformInput(openGLContext);
    //addSceneObject(scenePtr, "Triangle Uniform Input");
    //
    //scenePtr = new Sc5Texture(openGLContext);
    //addSceneObject(scenePtr,"Square Textured");
    //
    //scenePtr = new Sc6Box3DPerspective(openGLContext);
    //addSceneObject(scenePtr, "Box in 3D space");

    scenePtr = new Sc7Box3DCam(openGLContext);
    addSceneObject(scenePtr, "Box 3D Camera");

    scenePtr = new Sc8Lighting(openGLContext);
    addSceneObject(scenePtr, "Box with lighting");

    scenePtr = new Sc9LightingMaps(openGLContext);
    addSceneObject(scenePtr, "Box with lighting maps");

    scenePtr = new Sc10ManyCubesLM(openGLContext);
    addSceneObject(scenePtr, "Many boxes with lighting maps (FPS)");

    //Configuring the scene combo-box to select the current scene
    for(size_t i = 0; i < getScenesNumber(); ++i) {
        globalMainWindowFormUI->sceneSelectorComboBox->addItem(getSceneName(i));
    }
    QObject::connect(globalMainWindowFormUI->sceneSelectorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChangedCurrentIndex(int)));
    setCurrentSceneObjectIndex(0);
}

void SceneManager::final()
{
    for (size_t i = 0; i < sceneObjectsList.size(); i++) {
        //sceneObjectsList[i]->~SceneManager();
        //prevents calling finishScene() for inactive scenes(after change current scene)
        if(i == current_object_index) {
            sceneObjectsList[i]->finishScene();
        }
        delete sceneObjectsList[i];
	}
}

void SceneManager::addSceneObject(SceneManager* newSceneObjectPtr, const QString sceneName)
{
    sceneObjectsList.push_back(newSceneObjectPtr);
	sceneObjectsNamesList.push_back(sceneName);
    sceneObjectsInitStatusList.push_back(false);
}

void SceneManager::setCurrentSceneObjectIndex(size_t new_сurrent_index)
{
    if (current_object_index == new_сurrent_index) {
		return;
	}
    sceneObjectsInitStatusList[current_object_index] = false;
    sceneObjectsList[current_object_index]->finishScene();
    sceneObjectsList[current_object_index]->deleteUiOptionsWidget();
    current_object_index = new_сurrent_index;
}

QString SceneManager::getSceneName(size_t index)
{
    return sceneObjectsNamesList[index];
}

size_t SceneManager::getScenesNumber()
{
    return sceneObjectsList.size();
}

void SceneManager::initScene(int start_window_width, int start_window_height)
{
    (void)start_window_width;
    (void)start_window_height;
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

void SceneManager::resizeSceneWindow(int w, int h)
{
    (void)w;
    (void)h;
    //DON'T USE
}

void SceneManager::mousePressEventHandler(QMouseEvent event)
{
    (void)event;
    //DON'T USE
}

void SceneManager::mouseReleaseEventHandler(QMouseEvent event)
{
    (void)event;
    //DON'T USE
}

void SceneManager::mouseMoveEventHandler(QMouseEvent event)
{
    (void)event;
    //DON'T USE
}

void SceneManager::keyPressEventHandler(QKeyEvent* event)
{
    (void)event;
    //DON'T USE
}

void SceneManager::keyReleaseEventHandler(QKeyEvent* event)
{
    (void)event;
    //DON'T USE
}

void SceneManager::createUiOptionsWidget()
{
    //DON'T USE
}

void SceneManager::deleteUiOptionsWidget()
{
    //DON'T USE
}

void SceneManager::callInitSceneAndOptionsWidget(int start_window_width, int start_window_height)
{
	if (sceneObjectsList.size() == 0) {
		return;
	}
    if (sceneObjectsInitStatusList[current_object_index] == false) {
        sceneObjectsInitStatusList[current_object_index] = true;
        sceneObjectsList[current_object_index]->initScene(start_window_width, start_window_height);
        sceneObjectsList[current_object_index]->createUiOptionsWidget();
		return;
	}
}

void SceneManager::callDrawScene()
{
	if (sceneObjectsList.size() == 0) {
		return;
	}
    sceneObjectsList[current_object_index]->drawScene();
}

void SceneManager::callResizeSceneWindow(int w, int h)
{
    if (sceneObjectsList.size() == 0) {
        return;
    }
    sceneObjectsList[current_object_index]->resizeSceneWindow(w, h);
}

void SceneManager::callMousePressEventHandler(QMouseEvent event)
{
    if (sceneObjectsList.size() == 0) {
        return;
    }
    sceneObjectsList[current_object_index]->mousePressEventHandler(event);
}

void SceneManager::callMouseReleaseEventHandler(QMouseEvent event)
{
    if (sceneObjectsList.size() == 0) {
        return;
    }
    sceneObjectsList[current_object_index]->mouseReleaseEventHandler(event);
}

void SceneManager::callMouseMoveEventHandler(QMouseEvent event)
{
    if (sceneObjectsList.size() == 0) {
        return;
    }
    sceneObjectsList[current_object_index]->mouseMoveEventHandler(event);
}

void SceneManager::callKeyPressEventHandler(QKeyEvent* event)
{
    if (sceneObjectsList.size() == 0) {
        return;
    }
    sceneObjectsList[current_object_index]->keyPressEventHandler(event);
}

void SceneManager::callKeyReleaseEventHandler(QKeyEvent* event)
{
    if (sceneObjectsList.size() == 0) {
        return;
    }
    sceneObjectsList[current_object_index]->keyReleaseEventHandler(event);
}

void SceneManager::comboBoxChangedCurrentIndex(int newIndex) {
    setCurrentSceneObjectIndex(newIndex);
}
