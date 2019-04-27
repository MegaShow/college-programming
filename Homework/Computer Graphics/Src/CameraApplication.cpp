#include "CameraApplication.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

const std::string CameraApplication::VERTEX_SHADER_FILENAME = "Shader/Vec3PosVec3ColorWithUniProj.vs.glsl";
const std::string CameraApplication::FRAGMENT_SHADER_FILENAME = "Shader/Vec3Color.fs.glsl";

CameraApplication::CameraApplication()
    : shader(VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME),
    camera(glm::vec3(0.0f, 0.0f, 3.0f)) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

CameraApplication::~CameraApplication() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void CameraApplication::update() {
    ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    static const char* itemHeader[3] = { "Projection", "View Changing", "First Person Shooting" };
    ImGui::Combo("Item", &item, itemHeader, 3);
    if (item == 0) {
        ImGui::SliderFloat3("Position", position, -5.0f, 5.0f);
        ImGui::SliderFloat3("Camera", cameraPosition, -100.0f, 100.0f);
        ImGui::RadioButton("Orthographic", &projectionType, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Perspective", &projectionType, 1);
        if (projectionType == 0) {
            ImGui::SliderFloat4("Left/Right/Bottom/Top", window, -10.0f, 10.0f);
        } else {
            ImGui::SliderFloat("Radian", radian, 0.0f, 180.0f);
            ImGui::SliderFloat2("Width/Height", radian + 1, 0.0f, 1000.0f);
        }
        ImGui::SliderFloat2("Near/Far", windowDis, 0.1f, 100.0f);
    } else if (item == 1) {
        ImGui::SliderFloat("Camera Radian", &cameraRadius, 0.0f, 20.0f);
    }
    ImGui::End();
    render();
}

void CameraApplication::input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.input(Camera::Forward, 0.02f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.input(Camera::Backward, 0.02f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.input(Camera::Left, 0.02f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.input(Camera::Right, 0.02f);
}

void CameraApplication::input(GLFWwindow * window, float xOffset, float yOffset) {
    camera.input(xOffset, yOffset);
}

void CameraApplication::input(GLFWwindow * window, float zOffset) {
    camera.input(zOffset);
}

void CameraApplication::render() {
    shader.use();
    if (item == 0) {
        if (projectionType == 0) {
            glm::mat4 projection = glm::ortho(window[0], window[1], window[2], window[3], windowDis[0], windowDis[1]);
            shader.setGlmMat4("projection", projection);
        } else {
            glm::mat4 projection = glm::perspective(glm::radians(radian[0]), radian[1] / radian[2], windowDis[0], windowDis[1]);
            shader.setGlmMat4("projection", projection);
        }
        glm::mat4 view = glm::lookAt(glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setGlmMat4("view", view);
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
        model = glm::translate(model, glm::vec3(position[0], position[1], position[2]));
        shader.setGlmMat4("model", model);
    } else if (item == 1) {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        float camX = std::sin(glfwGetTime()) * cameraRadius;
        float camZ = std::cos(glfwGetTime()) * cameraRadius;
        glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
        shader.setGlmMat4("projection", projection);
        shader.setGlmMat4("view", view);
        shader.setGlmMat4("model", model);
    } else if (item == 2) {
        glm::mat4 projection = camera.getProjection();
        glm::mat4 view = camera.getView();
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
        shader.setGlmMat4("projection", projection);
        shader.setGlmMat4("view", view);
        shader.setGlmMat4("model", model);
    }

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
