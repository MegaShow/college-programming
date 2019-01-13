#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LoginRegisterScene.h"
#include "UsersInfoScene.h"
#include "ModifyUserScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto gotoLoginScene = MenuItemFont::create("Login/Register", [](Ref *pSender)
    {
        Director::getInstance()->pushScene(LoginRegisterScene::createScene());
    });
    if (gotoLoginScene)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - gotoLoginScene->getContentSize().height / 2;
        gotoLoginScene->setPosition(Vec2(x, y));
    }

    auto gotoUsersScene = MenuItemFont::create("Users", [](Ref *pSender)
    {
        Director::getInstance()->pushScene(UsersInfoScene::createScene());
    });
    if (gotoUsersScene)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - gotoUsersScene->getContentSize().height / 2 - 50;
        gotoUsersScene->setPosition(Vec2(x, y));
    }

    auto gotoModifyScene = MenuItemFont::create("Modify", [](Ref *pSender)
    {
        Director::getInstance()->pushScene(ModifyUserScene::createScene());
    });
    if (gotoModifyScene)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - gotoModifyScene->getContentSize().height / 2 - 100;
        gotoModifyScene->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, gotoLoginScene, gotoUsersScene, gotoModifyScene, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
