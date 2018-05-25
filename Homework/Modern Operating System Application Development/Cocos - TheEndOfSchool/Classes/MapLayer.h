#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class MapLayer : public Layer {
public:
    static Layer* createLayer();
    virtual bool init();

    CREATE_FUNC(MapLayer);
};

#endif
