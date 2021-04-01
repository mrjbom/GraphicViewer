#ifndef SC9LIGHTINGMAPS_H
#define SC9LIGHTINGMAPS_H


/*
 * Demonstration of the operation of lighting using the Phong reflection model and light maps.
 * Part 2
 */


#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <GL/GLU.h>
#include "../../SceneManager.h"
#include "../../ShaderProgram.h"

#include "../../BasicObjects/ArrowPainter/ArrowPainter.h"

#include "../../Camera/Camera.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include "ui_Sc9LightingMapsOptionsForm.h"

class Sc9LightingMaps : public SceneManager
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    Ui::Sc9LightingMapsOptionsForm* uiOptionsForm = nullptr;
    QWidget* optionsFormWidget = nullptr;

private:
    int window_width = 0, window_height = 0;
    float mouse_last_xpos = 0;
    float mouse_last_ypos = 0;
    bool mouse_left_button_pressed = false;

    Camera* cam = nullptr;
    ArrowPainter* arrowPainter = nullptr;

    ShaderProgram* gBoxShaderProgram = nullptr;
    GLuint g_VAO_cube = 0;
    GLuint g_VBO_cube_vertexes = 0;
    GLuint g_VBO_cube_normals = 0;
    GLuint g_VBO_cube_metalbox_deffusemap_texcoords = 0;
    GLuint g_metalbox_deffusemap_texture = 0;
    GLuint g_metalbox_specularmap_texture = 0;
    ShaderProgram* gLightShaderProgram = nullptr;
    GLuint g_VAO_light = 0;
    glm::vec3 g_light_position = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);
    glm::mat4 rotation_matrix = glm::mat4(1.0f);

    float x_rot = 0;
    float y_rot = 0;
    float x_rotation_speed_in_degrees = 0;
    float y_rotation_speed_in_degrees = 0;
    float x_size_scale = 1;
    float y_size_scale = 1;
    float light_rotation_around_degress = 0.0f;
    glm::vec3 g_light_direction = glm::vec3(2.5f, 0.0f, 0.0f);
    glm::vec3 g_light_color = glm::vec3(1.0f, 1.0f, 1.0f);

public:
    Sc9LightingMaps(QOpenGLContext* openGLContext);
    ~Sc9LightingMaps();
    void initScene(int start_window_width, int start_window_height) override;
    void drawScene() override;
    void finishScene() override;
    void resizeSceneWindow(int w, int h) override;
    void mousePressEventHandler(QMouseEvent event) override;
    void mouseReleaseEventHandler(QMouseEvent event) override;
    void mouseMoveEventHandler(QMouseEvent event) override;
    void keyPressEventHandler(QKeyEvent* event) override;
    void keyReleaseEventHandler(QKeyEvent* event) override;
    void createUiOptionsWidget() override;
    void deleteUiOptionsWidget() override;

public slots:
    void setXRotSpeedValueFromSlider(int new_value);
    void setYRotSpeedValueFromSlider(int new_value);
    void setXSizeValueFromSlider(int new_value);
    void setYSizeValueFromSlider(int new_value);
    void setLightRotValueFromSlider(int new_value);
    void resetRotationsButtonClicked();
    void setXLightDistValueFromSlider(double new_value);
    void setYLightDistValueFromSlider(double new_value);
    void setZLightDistValueFromSlider(double new_value);
};

#endif // SC9LIGHTINGMAPS_H
