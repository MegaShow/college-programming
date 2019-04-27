#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "PointDrawApplication.h"

const std::string PointDrawApplication::VERTEX_SHADER_FILENAME = "Shader/Vec2PosWithUniColor.vs.glsl";
const std::string PointDrawApplication::FRAGMENT_SHADER_FILENAME = "Shader/Vec3Color.fs.glsl";

PointDrawApplication::PointDrawApplication() :
    shader(VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME),
    triangle(points, 800, 600),
    circle(radius, 800, 600) {

    float color[3] = { 1.0f, 0.0f, 0.0f };
    shader.use();
    shader.setVec3("uniColor", color);
}

PointDrawApplication::~PointDrawApplication() {}

void PointDrawApplication::update() {
    ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::SliderInt("Point Size", &pointSize, 1, 5)) {
        triangle.setAttr(pointSize, rasterization);
        circle.setAttr(pointSize);
    }
    ImGui::RadioButton("Triangle", &objectType, 0);
    if (objectType == 0) {
        if (ImGui::Checkbox("Rasterization", &rasterization)) {
            triangle.setAttr(pointSize, rasterization);
        }
        bool modify = false;
        modify |= ImGui::SliderInt("Point 1 X", points, -400, 400);
        ImGui::SameLine();
        modify |= ImGui::SliderInt("Point 1 Y", points + 1, -300, 300);
        modify |= ImGui::SliderInt("Point 2 X", points + 2, -400, 400);
        ImGui::SameLine();
        modify |= ImGui::SliderInt("Point 2 Y", points + 3, -300, 300);
        modify |= ImGui::SliderInt("Point 3 X", points + 4, -400, 400);
        ImGui::SameLine();
        modify |= ImGui::SliderInt("Point 3 Y", points + 5, -300, 300);
        if (modify) {
            triangle.set(points);
        }
    }
    ImGui::RadioButton("Circle", &objectType, 1);
    if (objectType == 1) {
        if (ImGui::SliderInt("Radius", &radius, 50, 250)) {
            circle.set(radius);
        }
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    render();
}

void PointDrawApplication::render() {
    if (objectType == 0) {
        triangle.draw();
    } else if (objectType == 1) {
        circle.draw();
    }
}
