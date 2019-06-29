#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "GameApp.h"
#include "ResourceManager.h"

const std::string SERVER_IP = "127.0.0.1";
const uint16_t SERVER_PORT = 2333;

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
    std::cout << "Connect to server " << SERVER_IP << ":" << SERVER_PORT << "..." << std::endl;
    if (!client.connect(SERVER_IP, SERVER_PORT)) {
        std::cout << "Fail to connect to server." << std::endl;
        exit(-1);
    }
    isReady = false;
}

void GameApp::clear() {
    if (renderer) delete renderer;
    if (table) delete table;
    if (food) delete food;
    if (body) delete body;
    if (head) delete head;
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
    Direction oldDir = dir;
    if (Keys[GLFW_KEY_W]) {
        dir = Top;
    } else if (Keys[GLFW_KEY_A]) {
        dir = Left;
    } else if (Keys[GLFW_KEY_S]) {
        dir = Bottom;
    } else if (Keys[GLFW_KEY_D]) {
        dir = Right;
    } else if (Keys[GLFW_KEY_ENTER]) {
        isReady = true;
    }
    if (oldDir != dir) {
        client.input(static_cast<char>(dir));
    }
}

void GameApp::update(float dt) {
    if (!client.isRunning) {
        time += dt;
        if (time < 1.0f) {
            return;
        }
        time -= 1.0f;

        std::vector<bool> ready = client.ping(isReady);
        if (ready.size() == 0) {
            std::cout << "Fail to connect server." << std::endl;
            exit(-1);
        }
        if (!client.isRunning && client.isBusy) {
            std::cout << "Server is busy." << std::endl;
            exit(-1);
        }
        std::cout << "You are player " << client.id << "." << std::endl;
        for (int i = 0; i < ready.size(); i++) {
            if (!ready[i]) {
                std::cout << "Waiting for player " << i << "..." << std::endl;
            }
        }
        return;
    }

    if (client.sync()) {
        std::cout << "Sync players' state." << std::endl;
    } else {
        std::cout << "Fail to connect server." << std::endl;
        exit(-1);
    }
    if (client.isWin) {
        std::cout << "Game End." << std::endl;
        exit(0);
    }
}

void GameApp::render() {
    table->draw(*renderer);
    for (int i = 0; i < client.snakeHead.size(); i++) {
        switch (static_cast<Direction>(client.dir[i])) {
        case Left:
            head->setRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Right:
            head->setRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Top:
            head->setRotate(270.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Bottom:
            head->setRotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        }
        head->setPosition(getHeadPos(client.snakeHead[i].first, client.snakeHead[i].second));
        head->draw(*renderer);
    }
    for (auto& p : client.snakeBody) {
        body->setPosition(getBodyPos(p.first, p.second));
        body->draw(*renderer);
    }
    food->setPosition(getFoodPos(client.food.first, client.food.second));
    food->draw(*renderer);
}
