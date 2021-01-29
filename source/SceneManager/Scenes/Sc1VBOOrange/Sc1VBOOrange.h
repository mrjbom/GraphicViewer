#ifndef SC1VBOORANGE_H
#define SC1VBOORANGE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../helpfulopenglfunctions.h"

class Sc1VBOOrange : public SceneManager
{
private:
    QOpenGLFunctions_3_3_Core* glFunctions = nullptr;

private:
    GLuint gShaderProgram = 0;
    GLuint gVBO = 0;

public:
    Sc1VBOOrange(QOpenGLContext* openGLContext);
    ~Sc1VBOOrange();
    void initScene();
    void drawScene();
    void finishScene();
};

#endif // SC1VBOORANGE_H
