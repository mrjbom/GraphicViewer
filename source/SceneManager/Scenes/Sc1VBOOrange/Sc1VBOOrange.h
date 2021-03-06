#ifndef SC1VBOORANGE_H
#define SC1VBOORANGE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include "ui_Sc1VBOOrangeOptionsForm.h"

class Sc1VBOOrange : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    Ui::Sc1VBOOrangeOptionsForm* uiOptionsForm = nullptr;
    QWidget* optionsFormWidget = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VBO = 0;

public:
    Sc1VBOOrange(QOpenGLContext* openGLContext);
    ~Sc1VBOOrange();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
};

#endif // SC1VBOORANGE_H
