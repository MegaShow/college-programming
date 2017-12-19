// 1001. 二叉树
#include <iostream>
#include <string>
using namespace std;

int main() {
  string pre, post;
  int var = 1;
  cin >> pre >> post;
  for (int i = 0; i < pre.size() - 1; i++) {
    for (int j = 1; j < post.size(); j++) {
      if (pre[i] == post[j] && pre[i+1] == post[j-1]) {
        var <<= 1;
      }
    }
  }
  cout << var;
}
