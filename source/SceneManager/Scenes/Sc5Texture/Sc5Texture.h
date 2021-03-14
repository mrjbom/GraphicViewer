#ifndef SC5TEXTURE_H
#define SC5TEXTURE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"
#include <QWidget>
#include <QSlider>
#include <QLabel>

class Sc5Texture : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

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
};

#endif // SC5TEXTURE_H
