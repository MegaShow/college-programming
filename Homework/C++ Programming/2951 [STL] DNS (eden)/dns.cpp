// MegaShow
#include "dns.h"

dns::dns(string ip) {
  _ip = ip;
}

vector<string>& dns::operator[](const string& domain) {
  return _map[domain];
}

void dns::nslookup(const string& domain) {
  cout << "Server: " << _ip << endl;
  if (_map.find(domain) == _map.end() || _map[domain].size() == 0) {
    cout << "Server can't find " << domain << endl;
  } else {
    for (auto &i :_map[domain]) {
      cout << "Name: " << domain << endl;
      cout << "Address: " << i << endl;
    }
  }
}
