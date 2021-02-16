#ifndef SC7BOX3DCAM_H
#define SC7BOX3DCAM_H


#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"

#include "../../Camera/Camera.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include <QSlider>
#include <QPushButton>

class Sc7Box3DCam : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    int window_width = 0, window_height = 0;
    float mouse_last_xpos = 0;
    float mouse_last_ypos = 0;
    float mouse_left_button_pressed = false;

    Camera* cam = nullptr;

    ShaderProgram* gShaderProgram = nullptr;
    GLuint g_VAO_box = 0;
    GLuint g_VAO_box2 = 0;
    GLuint g_VBO_box_vertexes = 0;
    GLuint g_VBO_box_vertexes2 = 0;
    GLuint g_VBO_box_wall_texcoords = 0;
    GLuint g_VBO_box_wall_texcoords2 = 0;
    GLuint g_texture_box_wall = 0;
    GLuint g_texture_box_wall2 = 0;

    glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);
    glm::mat4 replication_matrix = glm::mat4(1.0f);

    float x_rot = 0;
    float y_rot = 0;
    float x_rotation_speed_in_degrees = 0;
    float y_rotation_speed_in_degrees = 0;

    QSlider* xRotationSpeedSlider = nullptr;
    QSlider* yRotationSpeedSlider = nullptr;
    QPushButton* rotationsResetButton = nullptr;

public:
    Sc7Box3DCam(QOpenGLContext* openGLContext);
    ~Sc7Box3DCam();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
    void resizeSceneWindow(int w, int h) override;
    void mousePressEventHandler(QMouseEvent* event) override;
    void mouseReleaseEventHandler(QMouseEvent* event) override;
    void mouseMoveEventHandler(QMouseEvent* event) override;
    void keyPressEventHandler(QKeyEvent* event) override;
    void keyReleaseEventHandler(QKeyEvent* event) override;

    void createUiOptionsWidgets() override;
    void deleteUiOptionsWidgets() override;

public slots:
    void setXRotSpeedValueFromSlider(int new_value);
    void setYRotSpeedValueFromSlider(int new_value);
    void resetRotationsButtonClicked();
};

#endif // SC7BOX3DCAM_H
