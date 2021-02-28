#ifndef SC8LIGHTING_H
#define SC8LIGHTING_H


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

class Sc8Lighting : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;

private:
    int window_width = 0, window_height = 0;
    float mouse_last_xpos = 0;
    float mouse_last_ypos = 0;
    float mouse_left_button_pressed = false;

    Camera* cam = nullptr;

    ShaderProgram* gBoxShaderProgram = nullptr;
    GLuint g_VAO_box = 0;
    GLuint g_VBO_box_vertexes = 0;
    GLuint g_VBO_box_normals = 0;
    GLuint g_VBO_box_wall_texcoords = 0;
    GLuint g_texture_box_wall = 0;
    ShaderProgram* gLightShaderProgram = nullptr;
    GLuint g_VAO_light;
    glm::vec3 g_light_to_box_distance = glm::vec3(2.5f, 0.0f, 0.0f);
    glm::vec3 g_light_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 g_light_color = glm::vec3(1.0f, 1.0f, 0.7f);
    float light_rotation_around_box_degress = 0.0f;

    glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);
    glm::mat4 replication_matrix = glm::mat4(1.0f);

    QSlider* lightRotationSpeedSlider = nullptr;

public:
    Sc8Lighting(QOpenGLContext* openGLContext);
    ~Sc8Lighting();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
    void resizeSceneWindow(int w, int h) override;
    void mousePressEventHandler(QMouseEvent event) override;
    void mouseReleaseEventHandler(QMouseEvent event) override;
    void mouseMoveEventHandler(QMouseEvent event) override;
    void keyPressEventHandler(QKeyEvent* event) override;
    void keyReleaseEventHandler(QKeyEvent* event) override;

    void createUiOptionsWidgets() override;
    void deleteUiOptionsWidgets() override;

public slots:
    void setLightRotSpeedValueFromSlider(int new_value);
};

#endif // SC8LIGHTING_H
