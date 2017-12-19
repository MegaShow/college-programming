#ifndef DNS_H
#define DNS_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::vector;

class dns {
 private:
    string _ip;  // server ip
    map< string, vector<string> > _map;  // one domain mapping multiple ips
 public:
    explicit dns(string ip);  // constructor
    vector<string>& operator[](const string& domain);  // return mutable ip_set

    /*
     *  if the domain maps at least one ip
     *  fot example, the dns server ip is 114.114.114.114
     *  the domain name is www.baidu.com
     *  and it maps 123.125.114.144, 220.181.57.217, 180.149.132.47
     *  then you should output like bellow
     *
     *  Server: 114.114.114.114
     *  Name: www.baidu.com
     *  Address: 123.125.114.144
     *  Name: www.baidu.com
     *  Address: 220.181.57.217
     *  Name: www.baidu.com
     *  Address: 180.149.132.47
     *
     *  if the domain doesn't map ip
     *  fot example, the dns server ip is 8.8.8.8
     *  the domain name is www.google.com, and doesn't map ip
     *  then you should output like bellow
     *
     *  Server: 8.8.8.8
     *  Server can't find www.google.com
     */
    void nslookup(const string& domain);
};

#endif  // DNS_H

