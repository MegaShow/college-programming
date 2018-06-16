#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "cocos2d.h"
using namespace cocos2d;

class Factory :public cocos2d::Ref {
public:
	//��ȡ��������
	static Factory* getInstance();
	//����һ��������洢�������й���
	Sprite* createMonster();
	//�������е����й��ﶼ����ɫ�ƶ���ͨ�������������еĹ���ܷ���
	void moveMonster(Vec2 playerPos, float time);
	//�Ƴ�����
	void removeMonster(Sprite*);
	//�ж���ײ
	Sprite* collider(Rect rect);
	//��ʼ������֡����
	void initSpriteFrame();
private:
	Factory();
	Vector<Sprite*> monster;
	cocos2d::Vector<SpriteFrame*> monsterDead;
	static Factory* factory;
};

#endif
