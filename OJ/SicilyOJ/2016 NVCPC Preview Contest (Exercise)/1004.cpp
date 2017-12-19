// 1004. Tailmon Compares Numbers
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main() {
  string a, b;
  cin >> a >> b;
  while (a.size() < b.size()) {
    a.insert(0, 1, '0');
  }
  while (a.size() > b.size()) {
    b.insert(0, 1, '0');
  }
  int index = 0;
  while (index < a.size()) {
    if (a[index] < b[index]) {
      cout << '<' << endl;
      break;
    } else if (a[index] > b[index]) {
      cout << '>' << endl;
      break;
    } else {
      index++;
    }
  }
  if (index == a.size()) {
    cout << '=' << endl;
  }
}
