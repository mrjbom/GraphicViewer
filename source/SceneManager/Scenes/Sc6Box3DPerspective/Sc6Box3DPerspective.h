#ifndef SC6BOX3DPERSPECTIVE_H
#define SC6BOX3DPERSPECTIVE_H


#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"

#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#include <../../glm/gtc/type_ptr.hpp>

#include <QSlider>
#include <QPushButton>

class Sc6Box3DPerspective : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    int window_width = 0, window_height = 0;

    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VAO_box = 0;
    GLuint g_VBO_box_vertexes = 0;
    GLuint g_VBO_box_wall_texcoords = 0;
    GLuint g_texture_box_wall = 0;

    glm::mat4 rotation_matrix = glm::mat4(1.0f);
    glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);
    glm::mat4 replication_matrix = glm::mat4(1.0f);

    float x_rot = 0;
    float y_rot = 0;
    float x_rotation_speed_in_degrees = 0;
    float y_rotation_speed_in_degrees = 0;

public:
    Sc6Box3DPerspective(QOpenGLContext* openGLContext);
    ~Sc6Box3DPerspective();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
    void resizeSceneWindow(int w, int h) override;
};

#endif // SC6BOX3DPERSPECTIVE_H
