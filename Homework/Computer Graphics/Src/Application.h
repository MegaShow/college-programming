#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    virtual void update() = 0;

    virtual void input(GLFWwindow* window) {}
    virtual void input(GLFWwindow* window, float xOffset, float yOffset) {}
    virtual void input(GLFWwindow* window, float zOffset) {}
};
