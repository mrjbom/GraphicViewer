#ifndef SC3UNIFORMINPUT_H
#define SC3UNIFORMINPUT_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"

class Sc4UniformInput : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint gVAO = 0;
    GLuint gVBO = 0;

public:
    Sc4UniformInput(QOpenGLContext* openGLContext);
    ~Sc4UniformInput();
    void initScene() override;
    void drawScene() override;
    void finishScene() override;

    void createUiOptionsWidgets() override;
    void deleteUiOptionsWidgets() override;
};

#endif // SC3UNIFORMINPUT_H
