// 1022. 剪掉叶子节点
#include <cstdio>

typedef int T;
struct BinaryNode {
  T data; //store data
  BinaryNode *left, *right;
  BinaryNode(T d, BinaryNode *l=NULL, BinaryNode* r=NULL):data(d), left(l), right(r) {};
};

#include <cstdio>

void cutLeaves(BinaryNode* &root) {
  if (root == NULL) return;
  if (root->left == NULL && root->right == NULL) {
    BinaryNode* tmp = root;
    delete tmp;
    root = NULL;
  } else {
    cutLeaves(root->left);
    cutLeaves(root->right);
  }
}

int main() {}
