// 1001. 幂集问题
#include <iostream>
#include <vector>
using namespace std;

int func(int var, vector<int> v) {
  if (var == 0) {
    cout << "{";
    if (v.size() != 0) {
      cout << v[0];
    }
    for (int i = 1; i < v.size(); i++) {
      cout << "," << v[i];
    }
    cout << "}" << endl;
  } else {
    func(var - 1, v);
    v.push_back(var);
    func(var - 1, v);
  }
}

int main() {
  int num, var;
  cin >> num;
  while (num--) {
    cin >> var;
    func(var, vector<int>());
  }
}
