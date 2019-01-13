#include "UsersInfoScene.h"
#include "network\HttpClient.h"
#include "json\document.h"

#include "json/stringbuffer.h"
#include "json/writer.h"
#include "APIService.h"

using namespace cocos2d::network;
using namespace rapidjson;

cocos2d::Scene * UsersInfoScene::createScene()
{
    return UsersInfoScene::create();
}

bool UsersInfoScene::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto getUserButton = MenuItemFont::create("Get User", CC_CALLBACK_1(UsersInfoScene::getUserButtonCallback, this));
    if (getUserButton)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + getUserButton->getContentSize().height / 2;
        getUserButton->setPosition(Vec2(x, y));
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

    auto menu = Menu::create(getUserButton, backButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    limitInput = TextField::create("limit", "arial", 24);
    if (limitInput)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height - 100.0f;
        limitInput->setPosition(Vec2(x, y));
        this->addChild(limitInput, 1);
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

void UsersInfoScene::getUserButtonCallback(Ref * pSender)
{
    messageBox->setString("");
    APIService::GetUsersInfo(limitInput->getString(), [&](HttpClient* sender, HttpResponse* res) -> void
    {
        if (!res || !res->isSucceed())
        {
            return;
        }
        Document d = APIService::GetDocument(res);
        if (d["status"].GetBool() == false)
        {
            messageBox->setString(string("Get Users Failed\n") + d["msg"].GetString());
        }
        else
        {
            string msg;
            for (auto& data : d["data"].GetArray())
            {
                msg.append(string("Username: ") + data["username"].GetString() + "\nDeck:\n");
                for (auto& deck : data["deck"].GetArray())
                {
                    for (auto it = deck.MemberBegin(); it != deck.MemberEnd(); it++)
                    {
                        msg.append(string("  ") + it->name.GetString() + ": " + to_string(it->value.GetInt()) + "\n");
                    }
                    msg.append("  ---\n");
                }
                msg.append("---\n");
            }
            messageBox->setString(msg);
        }
    });
}
