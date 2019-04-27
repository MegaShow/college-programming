#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    enum Movement {
        Forward, Backward, Left, Right
    };

    glm::mat4 getProjection();
    glm::mat4 getView();
    void input(Movement dir, float time);
    void input(float xOffset, float yOffset, bool constrainPitch = true);
    void input(float zOffset);

private:
    void update();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float zoom;

    float speed;
    float mouseSensitivity;
};
