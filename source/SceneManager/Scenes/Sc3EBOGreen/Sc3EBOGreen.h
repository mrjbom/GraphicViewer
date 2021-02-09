#ifndef SC3EBOGREEN_H
#define SC3EBOGREEN_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../globalvars.h"
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include <QCheckBox>

class Sc3EBOGreen : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint gVBO = 0;
    GLuint gEBO = 0;

    bool gShowPolygonLines = false;

    QCheckBox* gShowPolygonLinesCheckBoxWidget = nullptr;


public:
    Sc3EBOGreen(QOpenGLContext* openGLContext);
    ~Sc3EBOGreen();
    void initScene() override;
    void drawScene() override;
    void finishScene() override;

    void createUiOptionsWidgets() override;
    void deleteUiOptionsWidgets() override;

public slots:
    void showPolygonLinesStateChanged(int state);
};

#endif // SC3EBOGREEN_H
