#ifndef _STATELAYER_H_
#define _STATELAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class StateLayer : public Layer {
public:
    static Layer* createLayer();
    virtual bool init();

    CREATE_FUNC(StateLayer);
private:
    void PlayerMove(Ref* object, int direction);
    void PlayerDead(Ref* object);
    void PlayerAttack(Ref* object);
    void updateHPBar(float dt);
    void updateTimer(float dt);

    ProgressTimer * hpBar;
    Label* timer;
	Label* killNumber;
    int time;
};

#endif
