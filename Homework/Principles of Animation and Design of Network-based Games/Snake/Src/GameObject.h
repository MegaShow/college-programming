#pragma once

#include <glm/glm.hpp>

#include "Model.h"
#include "SpriteRenderer.h"

class GameObject {
public:
    GameObject(Model& model, glm::vec3 scale);

    void draw(SpriteRenderer& render);
    void setPosition(glm::vec3 position);
    void setRotate(float radian, glm::vec3 rotate);

private:
    Model& model;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale;
    float radian = 0.0f;
    glm::vec3 rotate = glm::vec3(1.0f);
};
