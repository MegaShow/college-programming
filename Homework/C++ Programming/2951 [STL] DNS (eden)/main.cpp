#include <iostream>
#include <vector>
#include <string>
#include "dns.h"

using std::cin;
using std::endl;

int main() {
    {
        dns dns114("114.114.114.114");
        dns114["www.baidu.com"].push_back("123.125.114.144");
        dns114["www.baidu.com"].push_back("220.181.57.217");
        dns114["www.baidu.com"].push_back("180.149.132.47");
        dns114.nslookup("www.baidu.com");
        dns114.nslookup("www.google.com");
        cout << endl << endl;
    }

    {
        dns googleDNS("8.8.8.8");
        googleDNS["www.google.com"].push_back("173.194.117.180");
        googleDNS["www.google.com"].push_back("173.194.117.177");
        googleDNS["www.google.com"].push_back("173.194.117.176");
        googleDNS["www.google.com"].push_back("173.194.117.179");
        googleDNS.nslookup("www.google.com");

        googleDNS["www.google.com"].clear();
        googleDNS.nslookup("www.google.com");
        googleDNS.nslookup("www.baidu.com");

        cout << endl << endl;
    }

    {
        int T;
        string domainName, serverIP, ip;
        cin >> serverIP >> domainName;
        dns test(serverIP);

        cin >> T;
        for (int i = 0; i < T; i++) {
            cin >> ip;
            test[domainName].push_back(ip);
        }
        test.nslookup(domainName);
    }
    return 0;
}

