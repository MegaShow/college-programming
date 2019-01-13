// 1008. Size Balanced Tree
#include <cstdio>
#include <queue>
using namespace std;

typedef int T;

struct BinaryNode{
  T data; //store data
  int size;//number of nodes on the tree
  BinaryNode *left, *right;
  BinaryNode(T d, int s = 0, BinaryNode *l=NULL, BinaryNode* r=NULL):data(d),size(s), left(l), right(r) {};
};

void insert(BinaryNode* &root, const T &x){
  if (root == NULL) {
    root = new BinaryNode(x);
    return;
  }
  if (root->left == NULL && root->right == NULL) {
    root->right = new BinaryNode(x);
    root->size++;
  } else if (root->left == NULL) {
    root->left = new BinaryNode(x);
    root->size++;
  } else if (root->left->size == root->right->size) {
    insert(root->right, x);
    root->size++;
  } else {
    insert(root->left, x);
    root->size++;
  }
}

int main() {}
