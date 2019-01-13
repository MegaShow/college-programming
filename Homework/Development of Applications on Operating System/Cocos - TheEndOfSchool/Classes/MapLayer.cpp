#include "MapLayer.h"
#include "Player.h"
#include "Monster.h"

Layer * MapLayer::createLayer() {
	return MapLayer::create();
}

bool MapLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tmx = TMXTiledMap::create("map.tmx");
	tmx->setScale(tmx->getMapSize().width * tmx->getTileSize().width / tmx->getContentSize().width);
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(tmx, 0);

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
	auto attack = Animation::createWithSpriteFrames(attackSFV, 0.05f);
	auto dead = Animation::createWithSpriteFrames(deadSFV, 0.1f);
	auto run = Animation::createWithSpriteFrames(runSFV, 0.3f / 8);
	auto player = Player::createWithAnimation(attack, dead, run);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(player, 3);

	this->scheduleUpdate();
	this->schedule(schedule_selector(MapLayer::updateCreateMonster), 2.0f);
	this->schedule(schedule_selector(MapLayer::updateMoveMonster), 2.0f);
	return true;
}

void MapLayer::update(float dt) {
    auto player = Player::getInstance();
    auto monster = Factory::getInstance()->collider(player->getBoundingBox());
    if (monster != nullptr)
    {
        Factory::getInstance()->removeMonster(monster);
        double hp = player->Hit(15);
        if (hp <= 0)
        {
            this->unscheduleAllCallbacks();
        }
    }
}

void MapLayer::updateCreateMonster(float dt) {
	auto monster = Factory::getInstance()->createMonster();
	float x = random(0.f, this->getContentSize().width);
	float y = random(0.f, this->getContentSize().height);
	monster->setPosition(Vec2(x, y));
	this->addChild(monster, 2);
}

void MapLayer::updateMoveMonster(float dt) {
	Factory::getInstance()->moveMonster(Player::getInstance()->getPosition(), 1);
}
