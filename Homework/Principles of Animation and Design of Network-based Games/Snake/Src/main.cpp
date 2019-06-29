#include <functional>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameApp.h"
#include "ResourceManager.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GameApp app(SCR_WIDTH, SCR_HEIGHT);

bool cursorPosInit = true;
float cursorPosLastX;
float cursorPosLastY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Snake", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    ResourceManager::loadShader("object", "Shader/object.vs.glsl", "Shader/object.fs.glsl");
    ResourceManager::loadModel("apple", "Assets/Apple/Apple2.obj");
    ResourceManager::loadModel("balloon", "Assets/Balloon/Balloon.obj");
    ResourceManager::loadModel("orange", "Assets/Orange/Orange.obj");
    ResourceManager::loadModel("table", "Assets/Table/Table_Large_Rectangular_01.obj");
    app.init();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        app.input(deltaTime);
        app.update(deltaTime);
        app.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            app.Keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            app.Keys[key] = false;
        }
    }
}
