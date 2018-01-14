// 1486. 统计数字
#include <cstdio>
#include <map>
using namespace std;

int main() {
  int num, val;
  bool flag = false;
  while (~scanf("%d", &num)) {
    if (flag) printf("\n");
    flag = true;
    map<int, int> m;
    for (int i = 0; i < num; i++) {
      scanf("%d", &val);
      m[val]++;
    }
    map<int, int>::iterator it = m.begin();
    while (it != m.end()) {
      printf("%d %d\n", it->first, it->second);
      it++;
    }
  }
}
