// 1004
#include <cstdio>
#include <cmath>
#include <bitset>
#include <memory.h>
using namespace std;

const int id = 20001 * 20001;

bitset<id> arr;

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int w, h, n;
    int count = 0;
    arr.reset();
    scanf("%d%d%d", &w, &h, &n);
    for (int i = 0; i < n; i++) {
      int nw, nh, nr;
      scanf("%d%d%d", &nw, &nh, &nr);
      int size = 2 * nr + 1;
      for (int x = -nr; x <= nr; x++) {
        for (int y = -nr; y <= nr; y++) {
          if (nw + x >= w || nw + x < 0 || nh + y >= h || nh + y < 0) continue;
          if (!arr[(nw+x)*20001+nh+y] && x * x + y * y <= nr * nr) {
            arr[(nw+x)*20001+nh+y] = true;
            count++;
          }
        }
      }
    }
    printf("%d\n", w * h - count);
  }
}
