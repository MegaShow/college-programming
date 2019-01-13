#include "json/stringbuffer.h"
#include "json/writer.h"

#include "APIService.h"
#include "Singleton.h"

using namespace rapidjson;

const string APIService::baseUrl = "http://127.0.0.1:8000";

void APIService::Register(const string & username, const string & password, const ccHttpRequestCallback & callback)
{
    Document d;
    Value su, pu;
    d.SetObject();
    su.SetString(username.c_str(), d.GetAllocator());
    pu.SetString(password.c_str(), d.GetAllocator());
    d.AddMember("username", su, d.GetAllocator());
    d.AddMember("password", pu, d.GetAllocator());
    Singleton<Net>::getInstance()->Post(baseUrl + "/users", d, callback);
}

void APIService::Login(const string & username, const string & password, const ccHttpRequestCallback & callback)
{
    Document d;
    Value su, pu;
    d.SetObject();
    su.SetString(username.c_str(), d.GetAllocator());
    pu.SetString(password.c_str(), d.GetAllocator());
    d.AddMember("username", su, d.GetAllocator());
    d.AddMember("password", pu, d.GetAllocator());
    Singleton<Net>::getInstance()->Post(baseUrl + "/auth", d, callback);
}

void APIService::UpdateDeck(const string & deck, const ccHttpRequestCallback & callback)
{
    Document d;
    Document arr(kArrayType);
    arr.Parse(deck.c_str());
    d.SetObject();
    d.AddMember("deck", arr, d.GetAllocator());
    if (arr.HasParseError())
    {
        // throw arr.GetParseError();
        return;
    }
    Singleton<Net>::getInstance()->Put(baseUrl + "/users", d, callback);
}

void APIService::GetUsersInfo(const string& limit, const ccHttpRequestCallback & callback)
{
    Singleton<Net>::getInstance()->Get(baseUrl + "/users" + "?limit=" + limit, callback);
}

Document APIService::GetDocument(HttpResponse * res)
{
    auto v = res->getResponseData();
    string json(v->begin(), v->end());
    Document d;
    d.Parse(json.c_str());
    if (d.HasParseError())
    {
        // throw d.GetParseError();
    }
    return d;
}
