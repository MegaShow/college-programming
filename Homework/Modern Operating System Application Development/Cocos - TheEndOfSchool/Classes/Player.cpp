#include "Player.h"

Player* Player::player = nullptr;

Player::Player(Animation* attack, Animation* dead, Animation* run) {
    this->attack = Animate::create(attack);
    this->dead = Animate::create(dead);
    this->run = Animate::create(run);
    this->attack->retain();
    this->dead->retain();
    this->run->retain();
    this->hp = 100;
}

Player::~Player() {
    this->attack->release();
    this->dead->release();
    this->run->release();
}

Player* Player::getInstance() {
    return player;
}

Player* Player::create() {
    return nullptr;
}

Player* Player::createWithSpriteFrame(SpriteFrame* spriteFrame) {
    return nullptr;
}

Player* Player::createWithAnimation(Animation* attack, Animation* dead, Animation* run) {
    if (player) {
        CC_SAFE_DELETE(player);
    }
    player = new (std::nothrow) Player(attack, dead, run);
    if (player && attack && player->initWithSpriteFrame(attack->getFrames().front()->getSpriteFrame())) {
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player::Move(int direction) {
    const double scale = 30;
    Vec2 p;
    switch (direction) {
    case 0:
        p = Vec2(0, scale);
        break;
    case 2:
        p = Vec2(-scale, 0);
        break;
    case 4:
        p = Vec2(0, -scale);
        break;
    case 6:
        p = Vec2(scale, 0);
        break;
    default:
        return false;
    }
    if (this->getNumberOfRunningActions()) {
        return false;
    }
    Vec2 next = this->getPosition() + p;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (next.x < 30 || next.y < 30 || next.x > visibleSize.width || next.y > visibleSize.height - 30) {
        return false;
    }
    auto moveBy = MoveBy::create(0.5, p);
    auto spawn = Spawn::create(moveBy, this->run, nullptr);
    auto fn = CallFunc::create(CC_CALLBACK_0(Player::ResetSpriteFrame, this));
    auto sequence = Sequence::create(spawn, fn, nullptr);
    this->runAction(sequence);
    return true;
}

void Player::Dead() {
    if (this->getNumberOfRunningActions()) {
        return;
    }
    auto fn = CallFunc::create(CC_CALLBACK_0(Player::ResetSpriteFrame, this));
    auto sequence = Sequence::create(this->dead, fn, nullptr);
    this->runAction(sequence);
    this->hp = (this->hp - 15 < 0 ? 0 : this->hp - 15);
}

void Player::Attack() {
    if (this->getNumberOfRunningActions()) {
        return;
    }
    auto fn = CallFunc::create(CC_CALLBACK_0(Player::ResetSpriteFrame, this));
    auto sequence = Sequence::create(this->attack, fn, nullptr);
    this->runAction(sequence);
    this->hp = (this->hp + 15 > 100 ? 100 : this->hp + 15);
}

void Player::ResetSpriteFrame() {
    this->stopAllActions();
    this->setSpriteFrame(attack->getAnimation()->getFrames().front()->getSpriteFrame());
}

double Player::GetHP() {
    return hp;
}
