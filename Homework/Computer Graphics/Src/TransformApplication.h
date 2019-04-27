#pragma once

#include <string>

#include "Application.h"
#include "Shader.h"

class TransformApplication : public Application {
public:
    TransformApplication();
    ~TransformApplication();
    virtual void update();

private:
    void render();

    bool enableDepthTest = false;
    bool enableViewRadians = false;
    int transformType = 0;

    float translation = 0.0f;
    float translationStep = 0.05f;
    float translationVec3[3] = { 1.0f, 0.0f, 0.0f };
    float rotationVec3[3] = { 1.0f, 0.0f, 1.0f };
    float scale = 1.0f;
    float scaleStep = 0.05f;
    float moreScale = 0.8f;
    float moreScaleStep = 0.005f;

    Shader shader;

    unsigned int VAO[2], VBO[2];

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
