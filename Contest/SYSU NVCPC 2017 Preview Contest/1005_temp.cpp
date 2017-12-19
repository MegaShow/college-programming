// 1005
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m, val;
    vector<vector<int> > v;
    scanf("%d%d", &n, &m);
    vector<int> arr;
    for (int i = 0; i < n; i++) {
      arr.clear();
      for (int j = 0; j < m; j++) {
        scanf("%d", &val);
        arr.push_back(val);
      }
      v.push_back(arr);
    }
    sort(v.begin(), v.end(), [](vector<int> a, vector<int> b) {
      int vala = 0, valb = 0, suma = 0, sumb = 0;
      for (int i = 0; i < a.size(); i++) {
        if (a[i] >= 0) vala += a[i];
        if (b[i] >= 0) valb += b[i];
        suma += a[i];
        sumb += b[i];
      }
      vala += sumb;
      valb += suma;
      return vala > valb;
    });
    for (int i = 0; i < arr.size(); i++) {
      arr[i] = 0;
    }
    for (auto &x: v) {
      for (int j = 0; j < m; j++) {
        arr[j] += x[j];
        if (arr[j] < 0) arr[j] = 0;
      }
    }
    val = 0;
    for (int i = 0; i < arr.size(); i++) {
      val += arr[i];
    }
    printf("%d\n", val);
  }
}
