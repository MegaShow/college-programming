// 1009. Find Median
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int num, val;
    vector<int> v;
    cin >> num;
    for (int i = 0; i < num; i++) {
      cin >> val;
      v.push_back(val);
    }
    sort(v.begin(), v.end());
    cout << v[(v.size() - 1) / 2] << endl;
  }
}
