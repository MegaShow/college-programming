#ifndef __THUNDER_H__
#define __THUNDER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class Thunder : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Thunder);
private:
	void preloadMusic();
	void playBgm();

	void addTouchListener();
	void addKeyboardListener();

	void addEnemy(int n);
	void newEnemy();
	void update(float f);
	void fire();
	void explosion();
	void meet(EventCustom* event);
	void addCustomListener();
	void movePlane(char c);
	void Boom(Sprite* enemy);
	void stopAc();
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
	void meet1(EventCustom* event);
	bool isMove;
	bool isClick;
	char movekey;
	Size visibleSize;
	Sprite* player;
	list<Sprite*> bullets;
	list<Sprite*> enemys;
	cocos2d::Vector<SpriteFrame*> explore;
	int stoneType;
	// show bullets and enemys number
	Label* bulletsNum;
	Label* enemysNum;
};

#endif // __THUNDER_H__
