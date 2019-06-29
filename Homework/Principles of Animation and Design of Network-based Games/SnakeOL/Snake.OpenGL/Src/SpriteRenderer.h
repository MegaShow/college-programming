#pragma once

#include "Model.h"
#include "Shader.h"

class SpriteRenderer {
public:
    SpriteRenderer(SpriteRenderer& obj): shader(obj.shader) {}
    SpriteRenderer(Shader& shader, unsigned int width, unsigned int height);

    void drawSprite(Model& model, glm::vec3 position, glm::vec3 scale, float radian, glm::vec3 rotate);

private:
    Shader& shader;
};
