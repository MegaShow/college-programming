#include "ModifyUserScene.h"
#include "network\HttpClient.h"
#include "json\document.h"

#include "APIService.h"

using namespace cocos2d::network;

cocos2d::Scene * ModifyUserScene::createScene()
{
    return ModifyUserScene::create();
}

bool ModifyUserScene::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto postDeckButton = MenuItemFont::create("Post Deck", CC_CALLBACK_1(ModifyUserScene::putDeckButtonCallback, this));
    if (postDeckButton)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + postDeckButton->getContentSize().height / 2;
        postDeckButton->setPosition(Vec2(x, y));
    }

    auto backButton = MenuItemFont::create("Back", [](Ref* pSender)
    {
        Director::getInstance()->popScene();
    });
    if (backButton)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - backButton->getContentSize().height / 2;
        backButton->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(postDeckButton, backButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    deckInput = TextField::create("Deck json here", "arial", 24);
    if (deckInput)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - 100.0f;
        deckInput->setPosition(Vec2(x, y));
        this->addChild(deckInput, 1);
    }

    messageBox = Label::create("", "arial", 30);
    if (messageBox)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2;
        messageBox->setPosition(Vec2(x, y));
        this->addChild(messageBox, 1);
    }

    return true;
}

void ModifyUserScene::putDeckButtonCallback(Ref * pSender)
{
    APIService::UpdateDeck(deckInput->getString(), [&](HttpClient* sender, HttpResponse* res) -> void
    {
        if (!res || !res->isSucceed())
        {
            return;
        }
        Document d = APIService::GetDocument(res);
        if (d["status"].GetBool() == false)
        {
            messageBox->setString(string("PUT Failed\n") + d["msg"].GetString());
        }
        else
        {
            messageBox->setString("PUT OK\n");
        }
    });
}
