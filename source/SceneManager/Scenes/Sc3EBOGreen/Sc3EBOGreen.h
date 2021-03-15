#ifndef SC3EBOGREEN_H
#define SC3EBOGREEN_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../globalvars.h"
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include "ui_Sc3EBOGreenOptionsForm.h"

class Sc3EBOGreen : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    Ui::Sc3EBOGreenOptionsForm* uiOptionsForm = nullptr;
    QWidget* optionsFormWidget = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VBO = 0;
    GLuint g_EBO = 0;

    bool g_show_polygon_lines = false;

public:
    Sc3EBOGreen(QOpenGLContext* openGLContext);
    ~Sc3EBOGreen();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
    void createUiOptionsWidget() override;
    void deleteUiOptionsWidget() override;

public slots:
    void showPolygonLinesStateChanged(int state);
};

#endif // SC3EBOGREEN_H
