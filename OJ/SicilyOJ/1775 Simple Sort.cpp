// 1775. Simple Sort
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int entry_num, item_num, query_num;
    cin >> entry_num >> item_num;
    vector<pair<vector<int>, int> > arr(entry_num);
    for (int i = 0; i < entry_num; i++) {
      arr[i].first.resize(item_num);
      arr[i].second = i;
      for (int j = 0; j < item_num; j++) {
        cin >> arr[i].first[j];
      }
    }
    cin >> query_num;
    while (query_num--) {
      int val;
      vector<pair<int, int> > pro(item_num);
      for (int i = 0; i < item_num; i++) {
        cin >> val;
        pro[i] = { val, i };
      }
      stable_sort(pro.begin(), pro.end(), [](pair<int, int> a, pair<int, int> b) -> bool {
        return a.first < b.first;
      });
      stable_sort(arr.begin(), arr.end(), [&pro](pair<vector<int>, int> a, pair<vector<int>, int> b) {
        for (int i = 0; i < pro.size(); i++) {
          if (a.first[pro[i].second] != b.first[pro[i].second]) {
            return a.first[pro[i].second] < b.first[pro[i].second];
          }
        }
        return a.second < b.second;
      });
      if (arr.size()) cout << arr[0].second;
      for (int i = 1; i < arr.size(); i++) {
        cout << ' ' << arr[i].second;
      }
      cout << endl;
    }
  }
}
