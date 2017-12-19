// 1000. 寻找第k大数字(numberk)
#define Method 1

#if Method == 1


#include <cstdio>
#include <bitset>
using namespace std;

int arr[10000001];
bitset<20000001> tag(0);

void qSortByK(int* arr, int start, int end, int k) {
  if (start >= end) {
    return;
  }
  int var = arr[start];
  int left = start + 1, right = end - 1;
  while (left <= right) {
    while (arr[left] > var) {
      left++;
    }
    while (arr[right] < var) {
      right--;
    }
    if (left < right) {
      arr[right] = arr[left] ^ arr[right];
      arr[left] = arr[left] ^ arr[right];
      arr[right] = arr[left] ^ arr[right];
    }
  }
  arr[start] = arr[right];
  arr[right] = var;
  if (right < k) {
    qSortByK(arr, right + 1, end, k);
  } else if (right > k) {
    qSortByK(arr, start, right, k);
  }
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int var;
  int index = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &var);
    if (!tag.test(var + 1e7)) {
      arr[index++] = var;
      tag.set(var + 1e7);
    }
  }
  k--;
  if (k >= 0 && k < index) {
    qSortByK(arr, 0, index, k);
    printf("%d\n", arr[k]);
  }
}


#elif Method == 2


#include <cstdio>
#include <bitset>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, greater<int> > q;
bitset<20000001> tag;

int main() {
  int n, k, var;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", &var);
    if (!tag.test(var + 1e7)) {
      tag.set(var + 1e7);
      q.push(var);
    }
    if (q.size() > k) {
      q.pop();
    }
  }
  printf("%d\n", q.top());
}


#endif
