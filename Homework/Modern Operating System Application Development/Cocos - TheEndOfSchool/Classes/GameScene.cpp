#include "GameScene.h"
#include "StateLayer.h"
#include "MapLayer.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

Scene* GameScene::createScene() {
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto stateLayer = StateLayer::createLayer();
    auto mapLayer = MapLayer::createLayer();
    this->addChild(stateLayer, 4);
    this->addChild(mapLayer, 0);

    return true;
}
