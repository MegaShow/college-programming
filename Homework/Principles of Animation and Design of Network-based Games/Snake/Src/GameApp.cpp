#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameApp.h"
#include "ResourceManager.h"

GameApp::GameApp(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

GameApp::~GameApp() {
    clear();
}

void GameApp::init() {
    clear();
    srand((unsigned int) glfwGetTime());
    renderer = new SpriteRenderer(ResourceManager::getShader("object"), width, height);
    table = new GameObject(ResourceManager::getModel("table"), glm::vec3(1.0f));
    food = new GameObject(ResourceManager::getModel("orange"), glm::vec3(0.002f));
    body = new GameObject(ResourceManager::getModel("balloon"), glm::vec3(5.0f));
    head = new GameObject(ResourceManager::getModel("apple"), glm::vec3(1.2f));
    dir = Right;
    head->setRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    for (int i = 0; i <= 3; i++) {
        snakePos.push_front({ i, 5 });
    }
    generateFood();
}

void GameApp::generateFood() {
    foodPos.first = rand() % 10;
    foodPos.second = rand() % 12;
    while (std::find(snakePos.begin(), snakePos.end(), foodPos) != snakePos.end()) {
        foodPos.first = rand() % 10;
        foodPos.second = rand() % 12;
    }
}

void GameApp::clear() {
    if (renderer) delete renderer;
    if (table) delete table;
    if (food) delete food;
    if (body) delete body;
    if (head) delete head;
    snakePos.clear();
}

glm::vec3 GameApp::getFoodPos(int x, int z) {
    return glm::vec3(-6.0f + x, 8.0f, -0.5f + z);
}

glm::vec3 GameApp::getHeadPos(int x, int z) {
    return glm::vec3(-4.8f + x * 1.04f, 8.0f, -2.2f + z * 1.06f);
}

glm::vec3 GameApp::getBodyPos(int x, int z) {
    return glm::vec3(-4.8f + x * 1.04f, 8.0f, -1.8f + z * 1.02f);
}

void GameApp::input(float dt) {
    if (Keys[GLFW_KEY_W]) {
        dir = Top;
    } else if (Keys[GLFW_KEY_A]) {
        dir = Left;
    } else if (Keys[GLFW_KEY_S]) {
        dir = Bottom;
    } else if (Keys[GLFW_KEY_D]) {
        dir = Right;
    }
}

void GameApp::update(float dt) {
    time += dt;
    if (time < 1.0f) {
        return;
    }
    time -= 1.0f;
    std::pair<int, int> newPos = snakePos.front();
    switch (dir) {
    case GameApp::Left:
        newPos.first = (newPos.first - 1 + 10) % 10;
        head->setRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    case GameApp::Right:
        newPos.first = (newPos.first + 1) % 10;
        head->setRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    case GameApp::Top:
        newPos.second = (newPos.second - 1 + 12) % 12;
        head->setRotate(270.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    case GameApp::Bottom:
        newPos.second = (newPos.second + 1) % 12;
        head->setRotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    }
    if (std::find(snakePos.begin(), snakePos.end(), newPos) != snakePos.end()) {
        init();
        return;
    }
    snakePos.push_front(newPos);
    if (newPos == foodPos) {
        generateFood();
    } else {
        snakePos.pop_back();
    }
}

void GameApp::render() {
    table->draw(*renderer);
    for (auto it = snakePos.begin(); it != snakePos.end(); it++) {
        if (it == snakePos.begin()) {
            head->setPosition(getHeadPos(it->first, it->second));
            head->draw(*renderer);
        } else {
            body->setPosition(getBodyPos(it->first, it->second));
            body->draw(*renderer);
        }
    }
    food->setPosition(getFoodPos(foodPos.first, foodPos.second));
    food->draw(*renderer);
}
