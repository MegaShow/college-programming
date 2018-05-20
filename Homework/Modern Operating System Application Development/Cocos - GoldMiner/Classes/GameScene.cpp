#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    //add touch listener
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("level-sheet.plist");
    char totalFrames = 3;
    char frameName[20];
    Animation* mouseAnimation = Animation::create();

    for (int i = 0; i < totalFrames; i++) {
        sprintf(frameName, "gem-mouse-%d.png", i);
        mouseAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    mouseAnimation->setDelayPerUnit(0.1);
    AnimationCache::getInstance()->addAnimation(mouseAnimation, "mouseAnimation");

    auto bg = Sprite::create("level-background-0.jpg");
    float scaleX = visibleSize.width / bg->getContentSize().width;
    float scaleY = visibleSize.height / bg->getContentSize().height;
    bg->setScale(MIN(scaleX, scaleY));
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg, 0);

    auto shootItem = MenuItemFont::create("Shoot", CC_CALLBACK_1(GameScene::shootMenuCallback, this));
    auto menu = Menu::create(shootItem, NULL);
    shootItem->setPosition(Vec2(visibleSize.width + origin.x - 100, visibleSize.height + origin.y - 100));
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    stoneLayer = Layer::create();
    stoneLayer->setPosition(Vec2::ZERO);
    stoneLayer->setAnchorPoint(Vec2::ZERO);
    stone = Sprite::create("stone.png");
    stone->setPosition(Vec2(560, 480));
    stoneLayer->addChild(stone);
    this->addChild(stoneLayer, 1);

    mouseLayer = Layer::create();
    mouseLayer->setPosition(Vec2(0, visibleSize.height / 2 + origin.y));
    mouseLayer->setAnchorPoint(Vec2::ZERO);
    mouse = Sprite::createWithSpriteFrameName("gem-mouse-0.png");
    mouse->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
    mouseLayer->addChild(mouse);
    this->addChild(mouseLayer, 1);

    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    auto location = touch->getLocation();
    if (location.y >= Director::getInstance()->getVisibleSize().height / 640 * 420) {
        return false;
    } else if (Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(mouse) != 0) {
        return false;
    }

    auto cheese = Sprite::create("cheese.png");
    cheese->setPosition(location);
    this->addChild(cheese);

    if (mouseLayer->convertToWorldSpace(mouse->getPosition()).x < location.x) {
        mouse->setRotationY(0);
    } else {
        mouse->setRotationY(180);
    }

    auto moveTo = MoveTo::create(1, mouseLayer->convertToNodeSpace(location));
    auto mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("mouseAnimation"));
    mouse->runAction(moveTo);
    mouse->runAction(Repeat::create(mouseAnimate, 1 / mouseAnimate->getDuration()));

    auto delay = DelayTime::create(1);
    auto fadeOut = FadeOut::create(1);
    auto fn = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, cheese));
    auto sequence = Sequence::create(delay, fadeOut, fn, nullptr);
    cheese->runAction(sequence);
    return true;
}

void GameScene::shootMenuCallback(Ref * pSender) {
    auto shootStone = Sprite::create("stone.png");
    shootStone->setPosition(Vec2(560, 480));
    stoneLayer->addChild(shootStone);
    auto location = mouseLayer->convertToWorldSpace(mouse->getPosition());
    auto moveTo = MoveTo::create(0.5, stoneLayer->convertToNodeSpace(location));
    auto fadeOut = FadeOut::create(1);
    auto fn = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, shootStone));
    auto sequence = Sequence::create(moveTo, fadeOut, fn, nullptr);
    shootStone->runAction(sequence);

    mouse->stopAllActions();
    float x = random(0.f, Director::getInstance()->getVisibleSize().width);
    float y = random(0.f, Director::getInstance()->getVisibleSize().height / 640 * 420);

    if (mouseLayer->convertToWorldSpace(mouse->getPosition()).x < x) {
        mouse->setRotationY(0);
    } else {
        mouse->setRotationY(180);
    }

    auto mouseMoveTo = MoveTo::create(1, mouseLayer->convertToNodeSpace(Vec2(x, y)));
    auto mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("mouseAnimation"));
    auto mouseSpawn = Spawn::create(mouseMoveTo, Repeat::create(mouseAnimate, 1 / mouseAnimate->getDuration()), nullptr);
    mouse->runAction(mouseSpawn);

    auto diamond = Sprite::create("diamond.png");
    diamond->setScale(0.5);
    diamond->setPosition(location);
    this->addChild(diamond);
}
