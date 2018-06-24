#ifndef __NET_H__
#define __NET_H__

#include <string>
#include "json/document.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;
using namespace rapidjson;
using namespace std;

class Net final
{
public:
    Net();

    void Get(const string& url, const ccHttpRequestCallback& callback);
    void Post(const string& url, const Document& query, const ccHttpRequestCallback& callback);
    void Put(const string& url, const Document& query, const ccHttpRequestCallback& callback);
};

#endif
