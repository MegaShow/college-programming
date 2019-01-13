#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
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
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto customItem = MenuItemFont::create("Click Me", CC_CALLBACK_1(HelloWorld::menuCustomCallback, this));

    if (customItem == nullptr || closeItem == nullptr) {
        problemLoading("Fail to create MenuItemFont");
    } else {
        customItem->setColor(Color3B::BLACK);
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + 100 + customItem->getContentSize().height / 2;
        customItem->setPosition(Vec2(x, y));
    }

    auto menu2 = Menu::create(customItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto dict = Dictionary::createWithContentsOfFile("zh_cn.xml");
    auto name = (String*) dict->objectForKey("name");
    auto studentId = (String*) dict->objectForKey("studentId");

    auto label = Label::createWithSystemFont(name->getCString(), "DengXian", 36);
    if (label == nullptr) {
        problemLoading("System Font 'DengXian'");
    } else {
        label->setDimensions(label->getContentSize().width, 100);
        label->setTextColor(Color4B::BLUE);
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    auto label2 = Label::createWithTTF(studentId->getCString(), "fonts/Marker Felt.ttf", 24);
    if (label2 == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    } else if (label != nullptr) {
        label2->setTextColor(Color4B::BLACK);
        label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height - label2->getContentSize().height));
        this->addChild(label2, 1);
    }

    auto sprite = Sprite::create("Background.png");
    float scaleW = visibleSize.width / sprite->getContentSize().width;
    float scaleH = visibleSize.width / sprite->getContentSize().height;
    sprite->setScale(scaleW > scaleH ? scaleW : scaleH);
    if (sprite == nullptr) {
        problemLoading("'Background.png'");
    } else {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuCustomCallback(cocos2d::Ref * pSender) {
    auto menuItem = (MenuItemFont*) pSender;
    if (menuItem->getString() == "Click Me") {
        menuItem->setString("Don't Click Me");
    } else if (menuItem->getString() == "Don't Click Me") {
        menuItem->setString("Please, don't click me");
    } else {
        menuItem->setString("Emmm...");
    }
}
