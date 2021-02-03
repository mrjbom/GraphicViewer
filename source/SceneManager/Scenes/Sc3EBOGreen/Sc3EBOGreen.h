#ifndef SC3EBOGREEN_H
#define SC3EBOGREEN_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"

class Sc3EBOGreen : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint gVBO = 0;
    GLuint gEBO = 0;

public:
    Sc3EBOGreen(QOpenGLContext* openGLContext);
    ~Sc3EBOGreen();
    void initScene();
    void drawScene();
    void finishScene();
};

#endif // SC3EBOGREEN_H
