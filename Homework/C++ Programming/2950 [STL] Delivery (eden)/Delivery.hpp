#ifndef DELIVERY_HPP_
#define DELIVERY_HPP_

#include <vector>
#include <map>
#include <string>
using std::string;

std::vector<string> getInfoSort(std::vector<string> info) {
  std::map<string, string> m;
  for (auto &i :info) {
    std::size_t pos = i.find('|');
    if (m.find(i.substr(pos + 1)) == m.end()) {
      m[i.substr(pos + 1)] = i.substr(0, pos);
    } else if (m[i.substr(pos + 1)] > i.substr(0, pos)) {
      m[i.substr(pos + 1)] = i.substr(0, pos);
    }
  }
  std::map<string, string> tmp;
  for (auto &i: m) {
    tmp[i.second] = i.first;
  }
  std::vector<string> s;
  for (auto &i: tmp) {
    s.push_back(i.first + " : " + i.second);
  }
  return s;
}

#endif
