#include "StateLayer.h"
#include "Player.h"

Layer * StateLayer::createLayer() {
    return StateLayer::create();
}

bool StateLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //hp条
    Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
    Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

    //使用hp条设置progressBar
    hpBar = ProgressTimer::create(sp);
    hpBar->setScaleX(90);
    hpBar->setAnchorPoint(Vec2(0, 0));
    hpBar->setType(ProgressTimerType::BAR);
    hpBar->setBarChangeRate(Point(1, 0));
    hpBar->setMidpoint(Point(0, 1));
    hpBar->setPercentage(100);
    hpBar->setPosition(Vec2(origin.x + 14 * hpBar->getContentSize().width, origin.y + visibleSize.height - 2 * hpBar->getContentSize().height));
    this->addChild(hpBar, 1);
    sp0->setAnchorPoint(Vec2(0, 0));
    sp0->setPosition(Vec2(origin.x + hpBar->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
    this->addChild(sp0, 0);

    time = 150;
    timer = Label::createWithTTF("150", "fonts/arial.ttf", 36);
    timer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 80));
    this->addChild(timer, 0);

    auto menuLabelW = Label::createWithTTF("W", "fonts/arial.ttf", 36);
    auto menuLabelA = Label::createWithTTF("A", "fonts/arial.ttf", 36);
    auto menuLabelS = Label::createWithTTF("S", "fonts/arial.ttf", 36);
    auto menuLabelD = Label::createWithTTF("D", "fonts/arial.ttf", 36);
    auto menuLabelX = Label::createWithTTF("X", "fonts/arial.ttf", 36);
    auto menuLabelY = Label::createWithTTF("Y", "fonts/arial.ttf", 36);
    auto menuButtonW = MenuItemLabel::create(menuLabelW, CC_CALLBACK_1(StateLayer::PlayerMove, this, 0));
    auto menuButtonA = MenuItemLabel::create(menuLabelA, CC_CALLBACK_1(StateLayer::PlayerMove, this, 2));
    auto menuButtonS = MenuItemLabel::create(menuLabelS, CC_CALLBACK_1(StateLayer::PlayerMove, this, 4));
    auto menuButtonD = MenuItemLabel::create(menuLabelD, CC_CALLBACK_1(StateLayer::PlayerMove, this, 6));
    auto menuButtonX = MenuItemLabel::create(menuLabelX, CC_CALLBACK_1(StateLayer::PlayerDead, this));
    auto menuButtonY = MenuItemLabel::create(menuLabelY, CC_CALLBACK_1(StateLayer::PlayerAttack, this));

    Size buttonSize = menuButtonX->getContentSize();
    menuButtonW->setPosition(Vec2(-visibleSize.width / 2 + buttonSize.width * 3, -visibleSize.height / 2 + buttonSize.height * 3));
    menuButtonA->setPosition(Vec2(-visibleSize.width / 2 + buttonSize.width * 1.5, -visibleSize.height / 2 + buttonSize.height * 2));
    menuButtonS->setPosition(Vec2(-visibleSize.width / 2 + buttonSize.width * 3, -visibleSize.height / 2 + buttonSize.height * 1));
    menuButtonD->setPosition(Vec2(-visibleSize.width / 2 + buttonSize.width * 4.5, -visibleSize.height / 2 + buttonSize.height * 2));
    menuButtonX->setPosition(Vec2(visibleSize.width / 2 - buttonSize.width * 2.5, -visibleSize.height / 2 + buttonSize.height * 2));
    menuButtonY->setPosition(Vec2(visibleSize.width / 2 - buttonSize.width * 1.5, -visibleSize.height / 2 + buttonSize.height * 3));
    
    auto menu = Menu::create(menuButtonW, menuButtonA, menuButtonS, menuButtonD, menuButtonX, menuButtonY, nullptr);
    this->addChild(menu, 1);

    this->schedule(schedule_selector(StateLayer::updateHPBar), 0.1f);
    this->schedule(schedule_selector(StateLayer::updateTimer), 1);

    return true;
}

void StateLayer::updateHPBar(float dt) {
    if (hpBar->getPercentage() < Player::getInstance()->GetHP()) {
        hpBar->setPercentage(hpBar->getPercentage() + 1);
    } else if (hpBar->getPercentage() > Player::getInstance()->GetHP()) {
        hpBar->setPercentage(hpBar->getPercentage() - 1);
    }
}

void StateLayer::updateTimer(float dt) {
    if (time) {
        time--;
        std::ostringstream ss;
        ss << time;
        timer->setString(ss.str());
    }
}

void StateLayer::PlayerMove(Ref * object, int direction) {
    Player::getInstance()->Move(direction);
}

void StateLayer::PlayerDead(Ref * object) {
    Player::getInstance()->Dead();
}

void StateLayer::PlayerAttack(Ref * object) {
    Player::getInstance()->Attack();
}


