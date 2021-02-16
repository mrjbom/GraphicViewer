#ifndef SC0TEST_H
#define SC0TEST_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include "../../globalvars.h"

class Sc0Test : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VAO = 0;
    GLuint g_VBO = 0;
    GLuint g_сolors_VBO = 0;

    //UI
    QPushButton* gBtn = nullptr;

public:
    Sc0Test(QOpenGLContext* openGLContext);
    ~Sc0Test();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;

    //UI
    void createUiOptionsWidgets() override;
    void deleteUiOptionsWidgets() override;
};

#endif // SC0TEST_H
