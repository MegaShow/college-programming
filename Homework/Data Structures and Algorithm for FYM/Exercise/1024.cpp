// 1024. 求期望
#include <iostream>
#include <vector>
using namespace std;

double mean() {
  int n, ival;
  double sum = 0, dval;
  vector<int> v;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ival;
    v.push_back(ival);
  }
  for (int i = 0; i < n; i++) {
    cin >> dval;
    sum = sum + dval * v[i];
  }
  return sum;
}

int main() {
  cout << mean() << endl;
}
