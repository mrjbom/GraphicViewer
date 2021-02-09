#ifndef SC5TEXTURE_H
#define SC5TEXTURE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include <QWidget>
#include <QSlider>
#include <QLabel>

class Sc5Texture : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint gVAO = 0;
    GLuint gVBOvertexes = 0;
    GLuint gVBOWallTexcoords = 0;
    GLuint gVBOCatTexcoords = 0;
    GLuint gEBOindexes = 0;
    GLuint gWallTexture = 0;
    GLuint gCatTexture = 0;


    QLabel* gMixValueTextLabel = nullptr;
    QSlider* gMixValueSlider = nullptr;
    float gMixValue = 0;

public:
    Sc5Texture(QOpenGLContext* openGLContext);
    ~Sc5Texture();
    void initScene() override;
    void drawScene() override;
    void finishScene() override;

    void createUiOptionsWidgets() override;
    void deleteUiOptionsWidgets() override;

public slots:
    void setNewMixValueFromSlider(int newValue);
};

#endif // SC5TEXTURE_H
