#ifndef SC5TEXTURE_H
#define SC5TEXTURE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include "ui_Sc5TextureOptionsForm.h"

class Sc5Texture : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    Ui::Sc5TextureOptionsForm* uiOptionsForm = nullptr;
    QWidget* optionsFormWidget = nullptr;

private:
    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VAO = 0;
    GLuint g_VBO_vertexes = 0;
    GLuint g_VBO_wall_texcoords = 0;
    GLuint g_VBO_cat_texcoords = 0;
    GLuint g_EBO_indexes = 0;
    GLuint g_wall_texture = 0;
    GLuint g_cat_texture = 0;

    float g_mix_value = 0;

public:
    Sc5Texture(QOpenGLContext* openGLContext);
    ~Sc5Texture();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
    void createUiOptionsWidget() override;
    void deleteUiOptionsWidget() override;

public slots:
    void setNewMixValueFromSlider(int new_value);
};

#endif // SC5TEXTURE_H
