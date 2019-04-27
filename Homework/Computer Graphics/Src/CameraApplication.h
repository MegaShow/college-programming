#pragma once

#include <memory>
#include <string>

#include "Application.h"
#include "Shader.h"
#include "Camera.h"

class CameraApplication : public Application {
public:
    CameraApplication();
    ~CameraApplication();
    virtual void update();
    virtual void input(GLFWwindow* window);
    virtual void input(GLFWwindow* window, float xOffset, float yOffset);
    virtual void input(GLFWwindow* window, float zOffset);

private:
    void render();

    Camera camera;
    Shader shader;

    unsigned int VAO, VBO;

    int item = 0;
    int projectionType = 0;
    float position[3] = { -1.5f, 0.5f, -1.5f };
    float cameraPosition[3] = { 0.0f, 3.0f, 3.0f };
    float window[4] = { -4.0f, 4.0f, -3.0f, 3.f };
    float radian[3] = { 45.0f, 800.0f, 600.0f };
    float windowDis[2] = { 0.1f, 100.0f };
    float cameraRadius = 10.0f;
    bool disabledCursor = false;

    float vertices[216] = {
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 1.0f,
         2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 1.0f,
         2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 1.0f,
         2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 1.0f,
        -2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 1.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 1.0f,

        -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
         2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
         2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
         2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
        -2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
        -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,

        -2.0f,  2.0f,  2.0f, 1.0f, 1.0f, 0.0f,
        -2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
        -2.0f, -2.0f,  2.0f, 1.0f, 1.0f, 0.0f,
        -2.0f,  2.0f,  2.0f, 1.0f, 1.0f, 0.0f,

         2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 0.0f,
         2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
         2.0f, -2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
         2.0f, -2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
         2.0f, -2.0f,  2.0f, 0.0f, 1.0f, 0.0f,
         2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 0.0f,

        -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
         2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
         2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f,
         2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f,
        -2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,

        -2.0f,  2.0f, -2.0f, 1.0f, 0.5f, 0.0f,
         2.0f,  2.0f, -2.0f, 1.0f, 0.5f, 0.0f,
         2.0f,  2.0f,  2.0f, 1.0f, 0.5f, 0.0f,
         2.0f,  2.0f,  2.0f, 1.0f, 0.5f, 0.0f,
        -2.0f,  2.0f,  2.0f, 1.0f, 0.5f, 0.0f,
        -2.0f,  2.0f, -2.0f, 1.0f, 0.5f, 0.0f
    };

    static const std::string VERTEX_SHADER_FILENAME;
    static const std::string FRAGMENT_SHADER_FILENAME;
};
