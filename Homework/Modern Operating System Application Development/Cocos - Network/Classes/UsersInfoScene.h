#pragma once

#ifndef __USER_INFO_SCENE_H__
#define __USER_INFO_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class UsersInfoScene : public  cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void getUserButtonCallback(Ref *pSender);

    CREATE_FUNC(UsersInfoScene);

    TextField *limitInput;
    Label *messageBox;
};

#endif // !__USER_INFO_SCENE_H__
