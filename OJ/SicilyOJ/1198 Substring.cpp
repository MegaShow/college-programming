// 1001. Substring
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
  int num, var;
  string str;
  cin >> num;
  while (num--) {
    vector<string> v;
    cin >> var;
    for (int i = 0; i < var; i++) {
      cin >> str;
      v.push_back(str);
    }
    sort(v.begin(), v.end(), [](string a, string b)->bool {
      return a + b < b + a;
    });
    for (auto &i : v) {
      cout << i;
    }
    cout << endl;
  }
}
