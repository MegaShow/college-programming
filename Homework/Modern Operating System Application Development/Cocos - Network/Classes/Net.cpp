#include "json/stringbuffer.h"
#include "json/writer.h"

#include "Net.h"

Net::Net()
{
    HttpClient::getInstance()->enableCookies("cookies.co");
}

void Net::Get(const string& url, const ccHttpRequestCallback& callback)
{
    auto req = new HttpRequest();
    req->setRequestType(HttpRequest::Type::GET);
    req->setUrl(url);
    req->setResponseCallback(callback);
    HttpClient::getInstance()->send(req);
    req->release();
}

void Net::Post(const string& url, const Document& query, const ccHttpRequestCallback& callback)
{
    StringBuffer buf;
    Writer<StringBuffer> writer(buf);
    query.Accept(writer);

    auto req = new HttpRequest();
    req->setRequestType(HttpRequest::Type::POST);
    req->setUrl(url);
    req->setRequestData(buf.GetString(), buf.GetSize());
    req->setResponseCallback(callback);
    HttpClient::getInstance()->send(req);
    req->release();
}

void Net::Put(const string & url, const Document & query, const ccHttpRequestCallback & callback)
{
    StringBuffer buf;
    Writer<StringBuffer> writer(buf);
    query.Accept(writer);

    auto req = new HttpRequest();
    req->setRequestType(HttpRequest::Type::PUT);
    req->setUrl(url);
    req->setRequestData(buf.GetString(), buf.GetSize());
    req->setResponseCallback(callback);
    HttpClient::getInstance()->send(req);
    req->release();
}
