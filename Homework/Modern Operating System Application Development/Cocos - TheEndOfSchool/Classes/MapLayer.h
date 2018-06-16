#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class MapLayer : public Layer {
public:
    static Layer* createLayer();
    virtual bool init();

	void update(float dt);
	void updateCreateMonster(float dt);
	void updateMoveMonster(float dt);

    CREATE_FUNC(MapLayer);
};

#endif
