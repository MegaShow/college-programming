#pragma once

#ifndef __MODIFY_USER_SCENE_H__
#define __MODIFY_USER_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

class ModifyUserScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void putDeckButtonCallback(Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(ModifyUserScene);

    Label *messageBox;
    TextField *deckInput;
};

#endif
