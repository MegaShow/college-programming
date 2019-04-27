#pragma once

#include <string>

#include "Application.h"
#include "Shader.h"

class TriangleApplication : public Application {
public:
    TriangleApplication();
    ~TriangleApplication();
    virtual void update();

private:
    void render();

    Shader shader, shaderWithUniColor;

    int objectType = 2;

    const float pointVertices[6] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
    const float lineVertices[12] = {
        -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
    };
    const float colorfulTriVertices[18] = {
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    const float singleColorTriVertices[9] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
    };
    float color[3] = { 1.0f, 0.0f, 0.0f };
    const float moreTriVertices[18] = {
         0.0f,  0.3f, 0.0f,
        -0.3f,  0.0f, 0.0f,
         0.3f,  0.0f, 0.0f,
        -0.6f, -0.3f, 0.0f,
         0.0f, -0.3f, 0.0f,
         0.6f, -0.3f, 0.0f
    };
    const unsigned int moreTriIndices[9] = {
        0, 1, 2,
        1, 3, 4,
        2, 4, 5
    };

    unsigned int VAOs[5], VBOs[5], EBO;

    static const std::string VERTEX_SHADER_FILENAME;
    static const std::string VERTEX_WITH_UNIFORM_COLOR_SHADER_FILENAME;
    static const std::string FRAGMENT_SHADER_FILENAME;
};
