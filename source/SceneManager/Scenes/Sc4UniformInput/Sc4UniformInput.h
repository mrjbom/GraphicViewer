#ifndef SC4UNIFORMINPUT_H
#define SC4UNIFORMINPUT_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include "../../globalvars.h"
#include "ui_Sc4UniformInputOptionsForm.h"

class Sc4UniformInput : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    Ui::Sc4UniformInputOptionsForm* uiOptionsForm = nullptr;
    QWidget* optionsFormWidget = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VAO = 0;
    GLuint g_VBO = 0;

public:
    Sc4UniformInput(QOpenGLContext* openGLContext);
    ~Sc4UniformInput();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
};

#endif // SC4UNIFORMINPUT_H
