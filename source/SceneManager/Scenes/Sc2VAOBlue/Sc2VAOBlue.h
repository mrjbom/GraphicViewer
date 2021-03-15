#ifndef SC2VAOBLUE_H
#define SC2VAOBLUE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include "ui_Sc2VAOBlueOptionsForm.h"

class Sc2VAOBlue : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    Ui::Sc2VAOBlueOptionsForm* uiOptionsForm = nullptr;
    QWidget* optionsFormWidget = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VAO = 0;
    GLuint g_VBO = 0;

public:
    Sc2VAOBlue(QOpenGLContext* openGLContext);
    ~Sc2VAOBlue();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
};

#endif // SC2VAOBLUE_H
