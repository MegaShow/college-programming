#include "Player.h"
#include "Monster.h"

Player* Player::player = nullptr;

Player::Player(Animation* attack, Animation* dead, Animation* run) {
    this->attack = Animate::create(attack);
    this->dead = Animate::create(dead);
    this->run = Animate::create(run);
    this->attack->retain();
    this->dead->retain();
    this->run->retain();
    this->hp = 100;
	this->isDead = false;
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
	if (this->isDead) {
		return false;
	}
    const double scale = 30;
    Vec2 p;
    switch (direction) {
    case 0:
        p = Vec2(0, scale);
        break;
    case 2:
		this->setFlippedX(true);
        p = Vec2(-scale, 0);
        break;
    case 4:
        p = Vec2(0, -scale);
        break;
    case 6:
		this->setFlippedX(false);
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
    auto moveBy = MoveBy::create(0.3, p);
    auto spawn = Spawn::create(moveBy, this->run, nullptr);
    // auto fn = CallFunc::create(CC_CALLBACK_0(Player::ResetSpriteFrame, this));
    // auto sequence = Sequence::create(spawn, fn, nullptr);
    // this->runAction(sequence);
	this->runAction(spawn);
    return true;
}

void Player::Dead() {
    if (this->isDead) {
        return;
    }
	this->ResetSpriteFrame();
    this->runAction(this->dead);
	this->isDead = true;
}

void Player::Attack() {
    if (this->isDead || this->getNumberOfRunningActions()) {
        return;
    }
    auto fn = CallFunc::create(CC_CALLBACK_0(Player::ResetSpriteFrame, this));
	auto delay = DelayTime::create(0.3);
	auto checkFn = CallFunc::create(CC_CALLBACK_0(Player::CheckAttack, this));
    auto sequence = Sequence::create(this->attack, fn, nullptr);
	auto sequence2 = Sequence::create(delay, checkFn, nullptr);
	auto spawn = Spawn::create(sequence, sequence2, nullptr);
    this->runAction(spawn);
}

void Player::CheckAttack() {
	auto playerRect = this->getBoundingBox();
	auto monsterRect = Rect(playerRect.getMinX() - 40, playerRect.getMinY() - 20,
		playerRect.getMaxX() - playerRect.getMinX() + 80, playerRect.getMaxY() - playerRect.getMinY() + 40);
	auto monster = Factory::getInstance()->collider(monsterRect);
	if (monster != nullptr) {
		this->Cure(15);
		Factory::getInstance()->removeMonster(monster);
		int val = UserDefault::getInstance()->getIntegerForKey("Monster");
		UserDefault::getInstance()->setIntegerForKey("Monster", val + 1);
	}
}

void Player::ResetSpriteFrame() {
    this->stopAllActions();
    this->setSpriteFrame(attack->getAnimation()->getFrames().front()->getSpriteFrame());
}

double Player::GetHP() {
    return this->hp;
}

double Player::Hit(double x) {
	this->hp -= x;
	if (this->hp <= 0) {
		Dead();
		return 0;
	}
	return this->hp;
}

double Player::Cure(double x) {
	this->hp += x;
	if (this->hp > 100) {
		this->hp = 100;
	}
	return this->hp;
}
