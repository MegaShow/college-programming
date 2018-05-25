#include "MapLayer.h"
#include "Player.h"

Layer * MapLayer::createLayer() {
    return MapLayer::create();
}

bool MapLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto attackTexture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
    auto deadTexture = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
    auto runTexture = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
    Vector<SpriteFrame*> attackSFV, deadSFV, runSFV;
    for (int i = 0; i < 17; i++) {
        auto frame = SpriteFrame::createWithTexture(attackTexture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i, 0, 113, 113)));
        attackSFV.pushBack(frame);
    }
    for (int i = 0; i < 22; i++) {
        auto frame = SpriteFrame::createWithTexture(deadTexture, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
        deadSFV.pushBack(frame);
    }
    for (int i = 0; i < 8; i++) {
        auto frame = SpriteFrame::createWithTexture(runTexture, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
        runSFV.pushBack(frame);
    }
    auto attack = Animation::createWithSpriteFrames(attackSFV, 0.1f);
    auto dead = Animation::createWithSpriteFrames(deadSFV, 0.1f);
    auto run = Animation::createWithSpriteFrames(runSFV, 0.1f);
    auto player = Player::createWithAnimation(attack, dead, run);
    player->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(player, 3);

    return true;
}
