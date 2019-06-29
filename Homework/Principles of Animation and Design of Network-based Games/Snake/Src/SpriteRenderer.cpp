#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader, unsigned int width, unsigned int height): shader(shader) {
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 18.0f, 15.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setGlmMat4("projection", projection);
    shader.setGlmMat4("view", view);
    shader.setGlmVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setGlmVec3("lightPos", glm::vec3(0.0f, 18.0f, 15.0f));
    shader.setGlmVec3("viewPos", glm::vec3(0.0f, 18.0f, 15.0f));
}

void SpriteRenderer::drawSprite(Model& model, glm::vec3 position, glm::vec3 scale, float radian, glm::vec3 rotate) {
    shader.use();
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, position);
    modelMat = glm::scale(modelMat, scale);
    modelMat = glm::rotate(modelMat, glm::radians(radian), rotate);
    shader.setGlmMat4("model", modelMat);
    model.draw(shader);
}
