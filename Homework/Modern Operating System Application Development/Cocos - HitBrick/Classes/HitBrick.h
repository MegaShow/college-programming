#ifndef __HIT_BRICK_H__
#define __HIT_BRICK_H__

#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class HitBrick : public Layer
{
public:
    static PhysicsWorld* world;
    static cocos2d::Scene* createScene();
    void setPhysicsWorld(PhysicsWorld * world);
    virtual bool init();
    void setJoint();
    void addSprite();   // ��ӱ����͸��־���
    void addPlayer();   // ������
    void addListener(); // ��Ӽ�����

    void update(float dt);
    void updateShip(float dt);  // ���´���ƽ�����
    void BrickGeneraetd();  // ��������

    void onKeyPressed(EventKeyboard::KeyCode code, Event * event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event * event);
    bool onConcactBegin(PhysicsContact & contact);

    void preloadMusic();                   // Ԥ��������
    void GameOver();                      // ��Ϸ����
    void loadAnimation(string filepath); // ���ض���

    // ������˳���ť��Ӧ����
    void replayCallback(Ref * pSender);
    void exitCallback(Ref * pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HitBrick);

private:
    PhysicsWorld * m_world;
    Size visibleSize;
    Sprite* player;
    Sprite* ship;
    bool onBall;
    Sprite* ball;
    // �̶��ؽ�
    PhysicsJointPin * joint1;
    bool spHolded;
    int spFactor;
};

#endif // __HIT_BRICK_H__
