// 1003
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
using namespace std;

int main() {
  int t, n, k;
  char str[10];
  scanf("%d", &t);
  while (t--) {
    int m_sum = 0;
    int s_sum = 0;
    map<int, int> m;
    set<int> s;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%s%d", str, &k);
      if (strcmp(str, "insert") == 0) {
        m[k]++;
        m_sum++;
        if (s.count(k)) {
          s.erase(k);
          s_sum--;
        }
        else {
          s.insert(k);
          s_sum++;
        }
      } else {
        if (m.count(k)) {
          m[k]--;
          if (m[k] == 0) m.erase(k);
          m_sum--;
          if (s.count(k)) {
            s.erase(k);
            s_sum--;
          }
          else {
            s.insert(k);
            s_sum++;
          }
        }
      }
      if (m_sum - s_sum >= 2 && m.size() >= 2) printf("both\n");
      else if (m.size() >= 2) printf("hetero\n");
      else if (m_sum - s_sum >= 2) printf("homo\n");
      else printf("neither\n");
    }
  }
}
