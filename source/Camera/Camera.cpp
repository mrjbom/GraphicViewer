#include "Camera.h"

Camera::Camera(glm::vec3 cam_position, glm::vec3 cam_target, glm::vec3 up_vec)
{
    camera_position = cam_position;
    camera_target = cam_target;
    up_vector = up_vec;
    camera_direction = glm::normalize(camera_position - camera_target);
    camera_right = glm::normalize(glm::cross(up_vector, camera_direction));
    camera_up = glm::cross(camera_direction, camera_right);
}

Camera::~Camera()
{

}

void Camera::setPitch(float pitch)
{
    if(pitch > 89.0f) {
        pitch = 89.0f;
    }
    else if(pitch < -89.0f) {
        pitch = -89.0f;
    }

    camera_pitch = pitch;
}

void Camera::setYaw(float yaw)
{
    camera_yaw = yaw - 90.0f;
}

void Camera::setRoll(float roll)
{
    camera_roll = roll;
}

void Camera::setMouseSensitivity(float sensitivity)
{
    mouse_sensitivity = sensitivity;
}

void Camera::processMouseOffsets(float xoffset, float yoffset)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    setYaw(getYaw() + xoffset);
    setPitch(getPitch() + yoffset);
}

void Camera::setMoveSpeed(float move_speed)
{
    camera_move_speed = move_speed;
}

void Camera::setMoveDirectionFlagStatus(CameraMoveDirections f, bool status)
{
    camera_move_directions.set(f, status);
}

float Camera::getPitch()
{
    return camera_pitch;
}

float Camera::getYaw()
{
    return camera_yaw + 90.0f;
}

float Camera::getRoll()
{
    return camera_roll;
}

void Camera::update()
{
    camera_direction = glm::vec3(0.0f);
    camera_direction.x = glm::cos(glm::radians(camera_yaw)) * glm::cos(glm::radians(camera_pitch));
    camera_direction.y = glm::sin(glm::radians(camera_pitch));
    camera_direction.z = glm::sin(glm::radians(camera_yaw)) * glm::cos(glm::radians(camera_pitch));
    camera_direction = glm::normalize(camera_direction);
    camera_right = glm::normalize(glm::cross(camera_direction, up_vector));
    camera_up = glm::normalize(glm::cross(camera_right, camera_direction));

    //Move
    if(camera_move_directions.test(CameraMoveDirections::MOVE_FORWARD)) {
        camera_position += camera_direction * camera_move_speed;
    }
    if(camera_move_directions.test(CameraMoveDirections::MOVE_BACK)) {
        camera_position -= camera_direction * camera_move_speed;
    }
    if(camera_move_directions.test(CameraMoveDirections::MOVE_RIGHT)) {
        camera_position += camera_right * camera_move_speed;
    }
    if(camera_move_directions.test(CameraMoveDirections::MOVE_LEFT)) {
        camera_position -= camera_right * camera_move_speed;
    }
    if(camera_move_directions.test(CameraMoveDirections::MOVE_UP)) {
        camera_position += camera_up * camera_move_speed;
    }
    if(camera_move_directions.test(CameraMoveDirections::MOVE_DOWN)) {
        camera_position -= camera_up * camera_move_speed;
    }
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
}
