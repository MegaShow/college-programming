#include "LightApplication.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

const std::string LightApplication::VERTEX_SHADER_FILENAME = "Shader/Vec3PosVec3NormWithUniProj.vs.glsl";
const std::string LightApplication::FRAGMENT_SHADER_FILENAME = "Shader/Vec3ColorWithLight.fs.glsl";
const std::string LightApplication::LIGHT_FRAGMENT_SHADER_FILENAME = "Shader/Light.fs.glsl";

const std::string LightApplication::GOURAUD_VERTEX_SHADER_FILENAME = "Shader/Vec3PosWithLight.vs.glsl";
const std::string LightApplication::GOURAUD_FRAGMENT_SHADER_FILENAME = "Shader/Vec3Color.fs.glsl";

LightApplication::LightApplication()
    : shader(VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME),
    lightShader(VERTEX_SHADER_FILENAME, LIGHT_FRAGMENT_SHADER_FILENAME),
    gouraudShader(GOURAUD_VERTEX_SHADER_FILENAME, GOURAUD_FRAGMENT_SHADER_FILENAME) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.use();
    shader.setBool("needAmbient", true);
    shader.setBool("needDiffuse", true);
    shader.setBool("needSpecular", true);
    shader.setFloat("ambientFactor", ambientFactor);
    shader.setFloat("specularFactor", specularFactor);
    shader.setInt("specularPow", specularPow);
    shader.setGlmMat4("projection", projection);

    lightShader.use();
    lightShader.setGlmMat4("projection", projection);

    gouraudShader.use();
    gouraudShader.setBool("needAmbient", true);
    gouraudShader.setBool("needDiffuse", true);
    gouraudShader.setBool("needSpecular", true);
    gouraudShader.setFloat("ambientFactor", ambientFactor);
    gouraudShader.setFloat("specularFactor", specularFactor);
    gouraudShader.setInt("specularPow", specularPow);
    gouraudShader.setGlmMat4("projection", projection);

}

LightApplication::~LightApplication() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void LightApplication::update() {
    ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    static const char* itemHeader[2] = { "Phong Shading", "Gouraud Shading"};
    ImGui::Combo("Item", &item, itemHeader, 2);
    ImGui::Checkbox("Movable Light", &moveable);
    ImGui::SliderFloat3("Camera Position", cameraPosition, -10.0f, 10.0f);
    ImGui::SliderFloat3("Light Position", lightPosition, -10.0f, 10.0f);
    ImGui::SliderFloat3("Light Color", lightColor, 0.0f, 1.0f);
    if (ImGui::SliderFloat("Ambient Factor", &ambientFactor, 0.0f, 1.0f)) {
        shader.use();
        shader.setFloat("ambientFactor", ambientFactor);
        gouraudShader.use();
        gouraudShader.setFloat("ambientFactor", ambientFactor);
    }
    if (ImGui::SliderFloat("Specular Factor", &specularFactor, 0.0f, 1.0f)) {
        shader.use();
        shader.setFloat("specularFactor", specularFactor);
        gouraudShader.use();
        gouraudShader.setFloat("specularFactor", specularFactor);
    }
    if (ImGui::SliderInt("Specular Pow", &specularPow, 1, 256)) {
        shader.use();
        shader.setInt("specularPow", specularPow);
        gouraudShader.use();
        gouraudShader.setInt("specularPow", specularPow);
    }
    if (ImGui::Checkbox("Ambient", &needAmbient)) {
        shader.use();
        shader.setBool("needAmbient", needAmbient);
        gouraudShader.use();
        gouraudShader.setBool("needAmbient", needAmbient);
    }
    if (ImGui::Checkbox("Diffuse", &needDiffuse)) {
        shader.use();
        shader.setBool("needDiffuse", needDiffuse);
        gouraudShader.use();
        gouraudShader.setBool("needDiffuse", needDiffuse);
    }
    if (ImGui::Checkbox("Specular", &needSpecular)) {
        shader.use();
        shader.setBool("needSpecular", needSpecular);
        gouraudShader.use();
        gouraudShader.setBool("needSpecular", needSpecular);
    }
    ImGui::End();
    render();
}

void LightApplication::render() {
    glm::vec3 color = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);
    glm::vec3 pos;
    if (moveable) {
        float lightRadius = std::sqrt(lightPosition[0] * lightPosition[0] + lightPosition[2] * lightPosition[2]);
        float lightX = std::sin(glfwGetTime()) * lightRadius;
        float lightZ = std::cos(glfwGetTime()) * lightRadius;
        pos = glm::vec3(lightX, lightPosition[1], lightZ);
    } else {
        pos = glm::vec3(lightPosition[0], lightPosition[1], lightPosition[2]);
    }
    glm::vec3 cameraPos = glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
    glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f));
    if (item == 0) {
        shader.use();
        shader.setGlmVec3("lightPos", pos);
        shader.setGlmVec3("lightColor", color);
        shader.setGlmVec3("viewPos", cameraPos);
        shader.setGlmMat4("view", view);
        shader.setGlmMat4("model", model);
    } else {
        gouraudShader.use();
        gouraudShader.setGlmVec3("lightPos", pos);
        gouraudShader.setGlmVec3("lightColor", color);
        gouraudShader.setGlmVec3("viewPos", cameraPos);
        gouraudShader.setGlmMat4("view", view);
        gouraudShader.setGlmMat4("model", model);
    }

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    lightShader.use();
    model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::scale(model, glm::vec3(0.0625f));
    lightShader.setGlmVec3("lightColor", color);
    lightShader.setGlmMat4("view", view);
    lightShader.setGlmMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
