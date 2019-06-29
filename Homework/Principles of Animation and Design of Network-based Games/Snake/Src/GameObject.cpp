#include "GameObject.h"

GameObject::GameObject(Model& model, glm::vec3 scale) : model(model), scale(scale) {}

void GameObject::draw(SpriteRenderer& renderer) {
    renderer.drawSprite(model, position, scale, radian, rotate);
}

void GameObject::setPosition(glm::vec3 position) {
    this->position = position;
}

void GameObject::setRotate(float radian, glm::vec3 rotate) {
    this->radian = radian;
    this->rotate = rotate;
}
