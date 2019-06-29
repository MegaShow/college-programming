#pragma once

#include <list>

#include "GameClient.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

class GameApp {
public:
    GameApp(unsigned int width, unsigned int height);
    ~GameApp();

    void init();
    void input(float dt);
    void update(float dt);
    void render();

    bool Keys[1024];

private:
    GameClient client;

    void clear();
    // x: 0 ~ 9, z: 0 ~ 11
    glm::vec3 getFoodPos(int x, int z);
    glm::vec3 getHeadPos(int x, int z);
    glm::vec3 getBodyPos(int x, int z);

    enum Direction {
        Left = 0, Right = 1, Top = 2, Bottom = 3
    };

    Direction dir;
    std::list<std::pair<int, int>> snakePos;
    std::pair<int, int> foodPos;

    GameObject* table = nullptr;
    GameObject* food = nullptr;
    GameObject* body = nullptr;
    GameObject* head = nullptr;
    SpriteRenderer* renderer;

    float time = 0;
    unsigned int width;
    unsigned int height;

    bool isReady;
};
