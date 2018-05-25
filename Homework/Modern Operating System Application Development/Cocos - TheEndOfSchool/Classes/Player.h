#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class Player : public Sprite {
public:
    static Player* getInstance();

    static Player* create();
    static Player* createWithSpriteFrame(SpriteFrame* spriteFrame);
    static Player* createWithAnimation(Animation* attack, Animation* dead, Animation* run);
    
    bool Move(int direction);
    void Dead();
    void Attack();

    void ResetSpriteFrame();
    double GetHP();

private:
    Player(Animation* attack, Animation* dead, Animation* run);
    ~Player();

    static Player* player;
    
    Animate* attack;
    Animate* dead;
    Animate* run;

    double hp;
};

#endif
