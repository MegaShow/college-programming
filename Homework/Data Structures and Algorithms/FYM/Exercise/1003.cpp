// 1003. Width of Binary Trees
#include <cstdio>
#include <queue>
using namespace std;

typedef int T;

struct treeNode {
  T data;
  struct treeNode *left, *right;

  treeNode(T d, treeNode *l=NULL, treeNode *r=NULL):data(d),left(l),right(r){};
};

int width(const treeNode * root) {
  if (root == NULL) return 0;
  queue<pair<const treeNode*, int> > q;
  q.push(make_pair(root, 0));
  int level = 0;
  int max = 0;
  int count = 0;
  while (!q.empty()) {
    pair<const treeNode*, int> nq = q.front();
    q.pop();
    if (nq.second == level) {
      count++;
    } else {
      level++;
      if (count > max) max = count;
      count = 1;
    }
    if (nq.first->left) q.push(make_pair(nq.first->left, nq.second + 1));
    if (nq.first->right) q.push(make_pair(nq.first->right, nq.second + 1));
  }
  return max >= count ? max : count;
}

int main() {
  treeNode* root = new treeNode(2, new treeNode(7), new treeNode(5));
  root->left->left = new treeNode(2);
  root->left->right = new treeNode(6, new treeNode(5), new treeNode(11));
  root->right->left = new treeNode(4);
  root->right->right = new treeNode(9);
  printf("%d\n", width(root));
}