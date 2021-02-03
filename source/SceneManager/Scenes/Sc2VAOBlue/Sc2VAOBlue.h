#ifndef SC2VAOBLUE_H
#define SC2VAOBLUE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"

class Sc2VAOBlue : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint gVAO = 0;
    GLuint gVBO = 0;

public:
    Sc2VAOBlue(QOpenGLContext* openGLContext);
    ~Sc2VAOBlue();
    void initScene();
    void drawScene();
    void finishScene();
};

#endif // SC2VAOBLUE_H
