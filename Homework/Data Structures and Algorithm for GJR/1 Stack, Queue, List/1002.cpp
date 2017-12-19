// 1002. 双栈排序
#include <iostream>
#include <stack>
#include <climits>
using namespace std;

void CreateGraph(int* arr, int num, int** graph) {
  // 预先处理找到最小的arr[k], 最小值满足就是存在arr[k]<arr[i]<arr[j]的情况, 不满足就是不存在
  int small[num+1];
  small[num] = INT_MAX;
  for (int i = num - 1; i >= 0; i--) {
    small[i] = arr[i];
    if (small[i] > small[i+1]) {
      small[i] = small[i+1];
    }
  }
  // 打图表
  for (int i = 0; i < num; i++) {
    for (int j = i + 1; j < num; j++) {
      if (arr[i] < arr[j] && small[j+1] < arr[i]) {
        graph[i][j] = graph[j][i] = 1;
      }
    }
  }
}

void DrawColor(int* arr, int num, int** graph, int* color, int i, int c, bool& flag) {
  color[i] = c;
  //cout << i << " => " << c << endl;
  for (int j = 0; j < num; j++) {
    if (graph[i][j] == 1) {
      if (color[j] == c) {
        flag = false;
      } else if (color[j] == 0) {
        DrawColor(arr, num, graph, color, j, 3 - c, flag);
      }
    }
  }
}

int main() {
  int num, var;
  while (cin >> num) {
    int arr[num], color[num];
    int** graph = new int*[num];
    for (int i = 0; i < num; i++) {
      cin >> arr[i];
      color[i] = 0;
      graph[i] = new int[num];
      for (int j = 0; j < num; j++) {
        graph[i][j] = 0;
      }
    }
    CreateGraph(arr, num, graph);
    // 染色
    bool flag = true;
    for (int i = 0; i < num; i++) {
      if (color[i] == 0) {
        DrawColor(arr, num, graph, color, i, 1, flag);
      }
    }
    /* for (int i = 0; i < num; i++) {
      cout << color[i];
    }
    cout << endl; */
    if (flag == false) {
      cout << "0" << endl;
    } else {
      stack<int> s1, s2;
      int out = 1;
      for (int i = 0; i < num; i++) {
        if (color[i] == 1) {
          s1.push(arr[i]);
          cout << (i == 0 ? "a" : " a");
        } else {
          s2.push(arr[i]);
          cout << " c";
        }
        while ((!s1.empty() && s1.top() == out) || (!s2.empty() && s2.top() == out)) {
          if (!s1.empty() && s1.top() == out) {
            s1.pop();
            cout << " b";
            out++;
          } else {
            s2.pop();
            cout << " d";
            out++;
          }
        }
      }
      cout << endl;
    }
    for (int i = 0; i < num; i++) {
      delete [] graph[i];
    }
    delete [] graph;
  }
}
