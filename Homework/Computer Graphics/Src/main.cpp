#include <functional>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Application.h"
#include "TriangleApplication.h"
#include "PointDrawApplication.h"
#include "TransformApplication.h"
#include "CameraApplication.h"
#include "LightApplication.h"

TriangleApplication* triangleApp = nullptr;
PointDrawApplication* pointDrawApp = nullptr;
TransformApplication* transformApp = nullptr;
CameraApplication* cameraApp = nullptr;
LightApplication* lightApp = nullptr;

Application* app = nullptr;

bool cursorPosInit = true;
float cursorPosLastX;
float cursorPosLastY;

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "CG Homework", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    int appType;

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::Begin("Application", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::RadioButton("Hw2 Triangle", &appType, 0)) {
            if (!triangleApp) triangleApp = new TriangleApplication();
            app = triangleApp;
        }
        if (ImGui::RadioButton("Hw3 Point Draw", &appType, 1)) {
            if (!pointDrawApp) pointDrawApp = new PointDrawApplication();
            app = pointDrawApp;
        }
        if (ImGui::RadioButton("Hw4 Transformation", &appType, 2)) {
            if (!transformApp) transformApp = new TransformApplication();
            app = transformApp;
        }
        if (ImGui::RadioButton("Hw5 Camera", &appType, 3)) {
            if (!cameraApp) cameraApp = new CameraApplication();
            app = cameraApp;
        }
        if (ImGui::RadioButton("Hw6 Light and Shading", &appType, 4)) {
            if (!lightApp) lightApp = new LightApplication();
            app = lightApp;
        }
        ImGui::End();

        if (app) {
            app->input(window);
            app->update();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    delete triangleApp;
    delete pointDrawApp;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (app) {
        if (cursorPosInit) {
            cursorPosLastX = xpos;
            cursorPosLastY = ypos;
            cursorPosInit = false;
        }
        app->input(window, xpos - cursorPosLastX, cursorPosLastY - ypos);
        cursorPosLastX = xpos;
        cursorPosLastY = ypos;
    }
}

void scrollCallback(GLFWwindow * window, double xOffset, double yOffset) {
    if (app) {
        app->input(window, yOffset);
    }
}
