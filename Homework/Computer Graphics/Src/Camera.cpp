#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
    : front(0.0f, 0.0f, -1.0f), zoom(45.0f), speed(2.5f), mouseSensitivity(0.1f) {

    this->position = position;
    this->worldUp = worldUp;
    this->yaw = yaw;
    this->pitch = pitch;
    update();
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(glm::radians(zoom), 800.0f / 600.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::getView() {
    return glm::lookAt(position, position + front, up);
}

void Camera::input(Movement dir, float time) {
    float velocity = speed * time;
    switch (dir) {
    case Camera::Forward:
        position += front * velocity;
        break;
    case Camera::Backward:
        position -= front * velocity;
        break;
    case Camera::Left:
        position -= right * velocity;
        break;
    case Camera::Right:
        position += right * velocity;
        break;
    default:
        break;
    }
}

void Camera::input(float xOffset, float yOffset, bool constrainPitch) {
    yaw += xOffset * mouseSensitivity;
    pitch += yOffset * mouseSensitivity;
    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }
    update();
}

void Camera::input(float zOffset) {
    if (zoom >= 1.0f && zoom <= 45.0f) zoom -= zOffset;
    if (zoom <= 1.0f) zoom = 1.0f;
    if (zoom >= 45.0f) zoom = 45.0f;
}

void Camera::update() {
    front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front.y = std::sin(glm::radians(pitch));
    front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
