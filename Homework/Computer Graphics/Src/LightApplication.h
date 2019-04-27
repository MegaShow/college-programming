#pragma once

#include <memory>
#include <string>

#include "Application.h"
#include "Shader.h"
#include "Camera.h"

class LightApplication : public Application {
public:
    LightApplication();
    ~LightApplication();
    virtual void update();

private:
    void render();

    Shader shader, lightShader, gouraudShader;

    unsigned int VAO, VBO;

    int item = 0;
    bool moveable = false;
    bool needAmbient = true;
    bool needDiffuse = true;
    bool needSpecular = true;
    float ambientFactor = 0.1f;
    float specularFactor = 0.5f;
    int specularPow = 64;

    float cameraPosition[3] = { 3.0f, 3.0f, 6.0f };
    float lightPosition[3] = { -2.5f, 2.5f, -4.5f };
    float lightColor[3] = { 1.0f, 1.0f, 1.0f };

    float vertices[324] = {
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,

        -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,

        -2.0f,  2.0f,  2.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -2.0f, -2.0f,  2.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -2.0f,  2.0f,  2.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

         2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f, -2.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f, -2.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f,  2.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

        -2.0f,  2.0f, -2.0f, 1.0f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
         2.0f,  2.0f, -2.0f, 1.0f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
         2.0f,  2.0f,  2.0f, 1.0f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
         2.0f,  2.0f,  2.0f, 1.0f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
        -2.0f,  2.0f,  2.0f, 1.0f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
        -2.0f,  2.0f, -2.0f, 1.0f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f
    };

    static const std::string VERTEX_SHADER_FILENAME;
    static const std::string FRAGMENT_SHADER_FILENAME;
    static const std::string LIGHT_FRAGMENT_SHADER_FILENAME;
    
    static const std::string GOURAUD_VERTEX_SHADER_FILENAME;
    static const std::string GOURAUD_FRAGMENT_SHADER_FILENAME;
};
