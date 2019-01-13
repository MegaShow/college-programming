#ifndef __API_SERVICE_H__
#define __API_SERVICE_H__

#include "Net.h"

class APIService final
{
public:
    static void Register(const string& username, const string& password, const ccHttpRequestCallback& callback);
    static void Login(const string& username, const string& password, const ccHttpRequestCallback& callback);
    static void UpdateDeck(const string& deck, const ccHttpRequestCallback& callback);
    static void GetUsersInfo(const string& limit, const ccHttpRequestCallback& callback);

    static Document GetDocument(HttpResponse* res);
private:
    static const string baseUrl;
};

#endif
