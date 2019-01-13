#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Scene {
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
private:
    Sprite* player;
    Vector<SpriteFrame*> attack;
    Vector<SpriteFrame*> dead;
    Vector<SpriteFrame*> run;
    Vector<SpriteFrame*> idle;
    Size visibleSize;
    Vec2 origin;
    Label* time;
    int dtime;
    ProgressTimer* pT;
};

#endif
