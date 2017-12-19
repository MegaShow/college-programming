// 1000. Translation
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int main() {
  map<string, string> m;
  string str1, str2;
  char str[25];
  fgets(str, 25, stdin);
  while (str[0] != '\n') {
    stringstream ss;
    ss << str;
    ss >> str1 >> str2;
    m[str2] = str1;
    fgets(str, 25, stdin);
  }
  while (cin >> str1) {
    if (m.find(str1) != m.end()) {
      cout << m[str1] << endl;
    } else {
      cout << "eh" << endl;
    }
  }
}
