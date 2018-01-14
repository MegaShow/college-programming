// 1002. 吊灯游戏
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main() {
  int num, turn_on, turn_off;
  while (~scanf("%d%d%d", &num, &turn_on, &turn_off)) {
    int index_on = 0, index_off = 0;
    for (int i = 2; i < num; i++) {
      index_on = (index_on + turn_on) % i;
      index_off = (index_off + turn_off) % i;
    }
    index_on = (index_on + turn_on) % num;
    index_off = (index_off + index_on + 1) % num;
    printf("%d %d\n", index_on + 1, index_off + 1);
  }
}

/* int main() {
  int num, turn_on, turn_off;
  while (cin >> num >> turn_on >> turn_off) {
    if (num == 1) {
      cout << 1 << ' ' << 1 << endl;
      continue;
    }
    bool isDead[num];
    memset(isDead, 0, sizeof(isDead));
    int remain = num, index = 0, count = 0;
    while (remain != 1) {
      if (isDead[index] == false) count++;
      if (count == turn_on) {
        isDead[index] = true;
        remain--;
        count = 0;
      }
      index++;
      if (index == num) index = 0;
    }
    while (isDead[index]) {
      index++;
      if (index == num) index = 0;
    }
    cout << index + 1 << ' ';
    while (remain != num - 1) {
      if (isDead[index]) count++;
      if (count == turn_off) {
        isDead[index] = false;
        remain++;
        count = 0;
      }
      index++;
      if (index == num) index = 0;
    }
    while (isDead[index] == false) {
      index++;
      if (index == num) index = 0;
    }
    cout << index + 1 << endl;
  }
} */



void func(int num, int turn_on, int turn_off) {
  if (num == 1) {
    printf("1 1\n");
    return;
  }
  int arr[num + 1];
  for (int i = 1; i < num; i++) {
    arr[i] = i + 1;
  }
  arr[num] = 1;
  int index = 1, prev_index = num;
  while (arr[index] != index) {
    for (int i = 1; i < turn_on; i++) {
      prev_index = index;
      index = arr[index];
    }
    index = arr[prev_index] = arr[index];
  }
  printf("%d ", index);
  for (int i = 1; i < num; i++) {
    arr[i] = i + 1 + (index - 1 == i ? 1 : 0);
  }
  arr[num - 1] = (index == num ? 1 : num);
  arr[num] = 1 + (index == 1 ? 1 : 0);
  prev_index = (index == 1 ? num : index - 1);
  index = (index == num ? 1 : index + 1);
  while (arr[index] != index) {
    for (int i = 1; i < turn_off; i++) {
      prev_index = index;
      index = arr[index];
    }
    index = arr[prev_index] = arr[index];
  }
  printf("%d\n", index);
}

/*int main() {
  int num, turn_on, turn_off;
  while (~scanf("%d%d%d", &num, &turn_on, &turn_off)) {
    func(num, turn_on, turn_off);
  }
  // for (int i = 1; i <= 100; i++) {
  //   for (int j = 1; j <= 100; j++) {
  //     for (int k = 1; k <= 100; k++) {
  //       printf("Case: %d %d %d\n", i, j, k);
  //       func(i, j, k);
  //     }
  //   }
  // }
}*/