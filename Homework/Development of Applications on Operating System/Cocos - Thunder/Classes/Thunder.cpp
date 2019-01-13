#include "Thunder.h"
#include <algorithm>

USING_NS_CC;

using namespace CocosDenshion;

Scene* Thunder::createScene()
{
    auto scene = Scene::create();
    auto layer = Thunder::create();
    scene->addChild(layer);
    return scene;
}

bool Thunder::init()
{
    if (!Layer::init())
    {
        return false;
    }

    stoneType = 0;
    isMove = false;  // 是否点击飞船
    visibleSize = Director::getInstance()->getVisibleSize();

    // 创建背景
    auto bgsprite = Sprite::create("bg.jpg");
    bgsprite->setPosition(visibleSize / 2);
    bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width,
        visibleSize.height / bgsprite->getContentSize().height);
    this->addChild(bgsprite, 0);

    // 创建飞船
    player = Sprite::create("player.png");
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPosition(visibleSize.width / 2, player->getContentSize().height);
    player->setName("player");
    this->addChild(player, 1);

    // 显示陨石和子弹数量
    enemysNum = Label::createWithTTF("enemys: 0", "fonts/arial.TTF", 20);
    enemysNum->setColor(Color3B(255, 255, 255));
    enemysNum->setPosition(50, 60);
    this->addChild(enemysNum, 3);
    bulletsNum = Label::createWithTTF("bullets: 0", "fonts/arial.TTF", 20);
    bulletsNum->setColor(Color3B(255, 255, 255));
    bulletsNum->setPosition(50, 30);
    this->addChild(bulletsNum, 3);

    addEnemy(5);        // 初始化陨石
    preloadMusic();     // 预加载音乐
    playBgm();          // 播放背景音乐
    explosion();        // 创建爆炸帧动画

    // 添加监听器
    addTouchListener();
    addKeyboardListener();
    addCustomListener();

    // 调度器
    schedule(schedule_selector(Thunder::update), 0.04f, kRepeatForever, 0);

    return true;
}

//预加载音乐文件
void Thunder::preloadMusic()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("music/bgm.mp3");
    audio->preloadEffect("music/explore.wav");
    audio->preloadEffect("music/fire.wav");
}

//播放背景音乐
void Thunder::playBgm()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("music/bgm.mp3", true);
}

//初始化陨石
void Thunder::addEnemy(int n)
{
    enemys.clear();
    for (unsigned i = 0; i < 3; ++i)
    {
        char enemyPath[20];
        sprintf(enemyPath, "stone%d.png", 3 - i);
        double width = visibleSize.width / (n + 1.0),
            height = visibleSize.height - (50 * (i + 1));
        for (int j = 0; j < n; ++j)
        {
            auto enemy = Sprite::create(enemyPath);
            enemy->setAnchorPoint(Vec2(0.5, 0.5));
            enemy->setScale(0.5, 0.5);
            enemy->setPosition(width * (j + 1), height);
            enemys.push_back(enemy);
            addChild(enemy, 1);
        }
    }
}

// 陨石向下移动并生成新的一行(加分项)
void Thunder::newEnemy()
{
    bool gameOver = false;
    for (auto enemy : enemys)
    {
        Vec2 pos = enemy->getPosition();
        pos.y -= 50;
        enemy->setPosition(pos);
        if (enemy->getBoundingBox().getMinY() < player->getBoundingBox().getMinY())
        {
            gameOver = true;
        }
    }
    char enemyPath[20];
    sprintf(enemyPath, "stone%d.png", stoneType + 1);
    double width = visibleSize.width / (5 + 1.0),
        height = visibleSize.height - 50;
    for (unsigned i = 0; i < 5; i++)
    {
        auto enemy = Sprite::create(enemyPath);
        enemy->setAnchorPoint(Vec2(0.5, 0.5));
        enemy->setScale(0.5, 0.5);
        enemy->setPosition(width * (i + 0.5), height);
        enemys.push_back(enemy);
        addChild(enemy, 1);
    }
    stoneType++;
    if (stoneType == 3)
    {
        stoneType = 0;
    }
    if (gameOver)
    {
        stopAc();
    }
}

// 移动飞船
void Thunder::movePlane(char c)
{
    const float scale = 15;
    Vec2 pos(0, 0);
    auto boundingBox = player->getBoundingBox();
    switch (c)
    {
    case 'A':
        if (boundingBox.getMinX() < scale)
        {
            auto moveTo = MoveTo::create(0.05f, Vec2(boundingBox.getMidX() - boundingBox.getMinX(), player->getPositionY()));
            player->stopAllActions();
            player->runAction(moveTo);
            return;
        }
        pos.x -= scale;
        break;
    case 'D':
        if (boundingBox.getMaxX() > visibleSize.width - scale)
        {
            auto moveTo = MoveTo::create(0.05f, Vec2(visibleSize.width - (boundingBox.getMaxX() - boundingBox.getMidX()), player->getPositionY()));
            player->stopAllActions();
            player->runAction(moveTo);
            return;
        }
        pos.x += scale;
        break;
    default:
        return;
    }
    auto moveBy = MoveBy::create(0.1f, pos);
    player->runAction(moveBy);
}

//发射子弹
void Thunder::fire()
{
    auto bullet = Sprite::create("bullet.png");
    bullet->setAnchorPoint(Vec2(0.5, 0.5));
    bullets.push_back(bullet);
    bullet->setPosition(player->getPosition());
    addChild(bullet, 1);
    SimpleAudioEngine::getInstance()->playEffect("music/fire.wav", false);

    // 移除飞出屏幕外的子弹
    auto moveBy = MoveBy::create(1.0f, Vec2(0, visibleSize.height - bullet->getBoundingBox().getMinY()));
    auto fn = CallFunc::create([bullet, this]()
    {
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            if (*it == bullet)
            {
                bullets.erase(it);
                break;
            }
        }
        bullet->removeFromParentAndCleanup(true);
    });
    auto sequence = Sequence::create(moveBy, fn, nullptr);
    bullet->runAction(sequence);
}

// 切割爆炸动画帧
void Thunder::explosion()
{
    auto texture = Director::getInstance()->getTextureCache()->addImage("explosion.png");
    for (int i = 0; i < 5; i++)
    {
        auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(4 + 188 * i, 0, 188, 188)));
        explore.pushBack(frame);
    }
    for (int i = 0; i < 3; i++)
    {
        auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(4 + 188 * i, 188, 188, 188)));
        explore.pushBack(frame);
    }
}

void Thunder::update(float f)
{
    // 实时更新页面内陨石和子弹数量(不得删除)
    // 要求数量显示正确(加分项)
    char str[15];
    sprintf(str, "enemys: %d", enemys.size());
    enemysNum->setString(str);
    sprintf(str, "bullets: %d", bullets.size());
    bulletsNum->setString(str);

    // 飞船移动
    if (isMove)
        this->movePlane(movekey);

    static int ct = 0;
    static int dir = 4;
    ++ct;
    if (ct == 120)
        ct = 40, dir = -dir;
    else if (ct == 80)
    {
        dir = -dir;
        newEnemy();  // 陨石向下移动并生成新的一行(加分项)
    }
    else if (ct == 20)
        ct = 40, dir = -dir;

    //陨石左右移动
    for (Sprite* s : enemys)
    {
        if (s != NULL)
        {
            s->setPosition(s->getPosition() + Vec2(dir, 0));
        }
    }

    // 分发自定义事件
    EventCustom e("meet");
    _eventDispatcher->dispatchEvent(&e);
}

// 自定义碰撞事件
void Thunder::meet(EventCustom * event)
{
    auto bulletIt = bullets.begin();
    while (bulletIt != bullets.end())
    {
        auto enemyIt = enemys.begin();
        bool destroy = false;
        while (enemyIt != enemys.end())
        {
            if ((*bulletIt)->getPosition().getDistance((*enemyIt)->getPosition()) < 25)
            {
                auto animate = Animate::create(Animation::createWithSpriteFrames(explore, 0.05f, 1));
                auto fn = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParentAndCleanup, *enemyIt, true));
                auto sequence = Sequence::create(animate, fn, nullptr);
                (*enemyIt)->runAction(sequence);
                SimpleAudioEngine::getInstance()->playEffect("music/explore.wav");
                enemys.erase(enemyIt);
                (*bulletIt)->removeFromParentAndCleanup(true);
                bulletIt = bullets.erase(bulletIt);
                destroy = true;
                break;
            }
            else
            {
                enemyIt++;
            }
        }
        if (destroy == false)
        {
            bulletIt++;
        }
    }
    for (auto enemyIt = enemys.begin(); enemyIt != enemys.end(); enemyIt++)
    {
        if ((*enemyIt)->getPosition().getDistance(player->getPosition()) < 40)
        {
            auto animate = Animate::create(Animation::createWithSpriteFrames(explore, 0.05f, 1));
            auto fn = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParentAndCleanup, *enemyIt, true));
            auto sequence = Sequence::create(animate, fn, nullptr);
            (*enemyIt)->runAction(sequence);
            enemys.erase(enemyIt);
            this->stopAc();
            break;
        }
    }
}

void Thunder::stopAc()
{
    auto animate = Animate::create(Animation::createWithSpriteFrames(explore, 0.05f, 1));
    auto fn = CallFunc::create([this]() 
    {
        player->removeFromParentAndCleanup(true);
        auto gameOver = Sprite::create("gameOver.png");
        gameOver->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(gameOver);
    });
    auto sequence = Sequence::create(animate, fn, nullptr);
    player->runAction(sequence);
    SimpleAudioEngine::getInstance()->playEffect("music/explore.wav");
    _eventDispatcher->removeAllEventListeners();
    this->unscheduleAllCallbacks();
}

// 添加自定义监听器
void Thunder::addCustomListener()
{
    auto listener = EventListenerCustom::create("meet", CC_CALLBACK_1(Thunder::meet, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 添加键盘事件监听器
void Thunder::addKeyboardListener()
{
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Thunder::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Thunder::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, player);
}

void Thunder::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_A:
        movekey = 'A';
        isMove = true;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
    case EventKeyboard::KeyCode::KEY_D:
        movekey = 'D';
        isMove = true;
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        if (isClick == false)
        {
            fire();
        }
        break;
    }
}

void Thunder::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
        isMove = false;
        break;
    }
}

// 添加触摸事件监听器
void Thunder::addTouchListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Thunder::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Thunder::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(Thunder::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标点击发射炮弹
bool Thunder::onTouchBegan(Touch *touch, Event *event)
{
    if (touch->getLocation().getDistance(player->getPosition()) <= 30)
    {
        isClick = true;
    }
    else
    {
        fire();
    }
    return true;
}

void Thunder::onTouchEnded(Touch *touch, Event *event)
{
    isClick = false;
}

// 当鼠标按住飞船后可控制飞船移动 (加分项)
void Thunder::onTouchMoved(Touch *touch, Event *event)
{
    if (isClick)
    {
        Vec2 pos(touch->getDelta().x, 0);
        auto boundingBox = player->getBoundingBox();
        if (player->getPosition().x + pos.x < boundingBox.getMidX() - boundingBox.getMinX())
        {
            auto moveTo = MoveTo::create(0.05f, Vec2(boundingBox.getMidX() - boundingBox.getMinX(), player->getPositionY()));
            player->stopAllActions();
            player->runAction(moveTo);
            return;
        }
        else if (player->getPosition().x + pos.x > visibleSize.width - (boundingBox.getMaxX() - boundingBox.getMidX()))
        {
            auto moveTo = MoveTo::create(0.05f, Vec2(visibleSize.width - (boundingBox.getMaxX() - boundingBox.getMidX()), player->getPositionY()));
            player->stopAllActions();
            player->runAction(moveTo);
            return;
        }
        auto moveBy = MoveBy::create(0.1f, pos);
        player->runAction(moveBy);
    }
}
