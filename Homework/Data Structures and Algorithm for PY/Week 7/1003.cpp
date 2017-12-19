// 1003. 最长公共子序列
#include <cstring>
#include <cstdio>

int main() {
  int index;
  char str1[1001], str2[1001];
  while (~scanf("%s%s", str1, str2)) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int arr[2][1002];
    memset(arr, 0, sizeof(arr));
    index = 0;
    for (int i = 1; i <= len1; i++) {
      index ^= 1;
      for (int j = 1; j <= len2; j++) {
        if (str1[i-1] == str2[j-1]) {
          arr[index][j] = arr[index^1][j-1] + 1;
        } else if (arr[index^1][j] > arr[index][j-1]) {
          arr[index][j] = arr[index^1][j];
        } else {
          arr[index][j] = arr[index][j-1];
        }
      }
    }
    printf("%d\n", arr[index][len2]);
  }
}
