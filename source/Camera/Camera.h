#ifndef CAMERA_H
#define CAMERA_H

#include "../../glm/vec3.hpp"
#include "../../glm/vec4.hpp"
#include "../../glm/mat4x4.hpp"
#include "../../glm/ext/matrix_transform.hpp"
#include "../../glm/ext/matrix_clip_space.hpp"
#include "../../glm/ext/scalar_constants.hpp"
#include <bitset>
#include <QDebug>

enum CameraMoveDirections
{
    MOVE_FORWARD = 0,
    MOVE_BACK = 1,
    MOVE_RIGHT = 2,
    MOVE_LEFT = 3,
    MOVE_UP = 4,
    MOVE_DOWN = 5,
    MOVE_SHIFT = 6
};

class Camera
{
private:
    glm::vec3 up_vector = glm::vec3(0.0f);
    glm::vec3 camera_position = glm::vec3(0.0f);
    //The point the camera is looking at
    glm::vec3 camera_target = glm::vec3(0.0f);
    glm::vec3 camera_direction = glm::vec3(0.0f);
    glm::vec3 camera_up = glm::vec3(0.0f);
    glm::vec3 camera_right = glm::vec3(0.0f);
    glm::mat4 camera_view_matrix = glm::mat4(0.0f);
    float camera_pitch = 0.0f;
    float camera_yaw = 0.0f;
    float camera_roll = 0.0f;

    float camera_move_speed = 0.1f;
    float mouse_sensitivity = 0.1f;
    std::bitset<7> camera_move_directions;
public:
    Camera(glm::vec3 cam_position, glm::vec3 cam_target, glm::vec3 up_vector = glm::vec3(0.0, 1.0, 0.0));
    ~Camera();
    void setPitch(float pitch);
    void setYaw(float yaw);
    void setRoll(float roll);
    void setMouseSensitivity(float sensitivity);
    void processMouseOffsets(float xoffset, float yoffset);
    void setMoveSpeed(float move_speed);
    void setMoveDirectionFlagStatus(CameraMoveDirections f, bool status);
    glm::vec3 getPosition();
    float getPitch();
    float getYaw();
    float getRoll();
    void update();
    glm::mat4 getViewMatrix();
};

#endif
