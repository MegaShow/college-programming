// 1011. Find the external path length
#include <iostream>
#include <queue>
using namespace std;

typedef int T;

struct BinaryNode {
  T data; //store data
  BinaryNode *left, *right;
  BinaryNode(T d, BinaryNode *l=NULL, BinaryNode* r=NULL):data(d), left(l), right(r) {};
};

int externalPL(const BinaryNode* root) {
  if (root == NULL) return 0;
  int epl = 0;
  queue<pair<const BinaryNode*, int> > q;
  q.push({ root, 0 });
  while (q.size()) {
    pair<const BinaryNode*, int> n = q.front();
    q.pop();
    if (n.first->left == NULL && n.first->right == NULL) epl = epl + n.second;
    if (n.first->left) q.push({ n.first->left, n.second + 1 });
    if (n.first->right) q.push({ n.first->right, n.second + 1 });
  }
  return epl;
}

int main() {
#define B BinaryNode
  B* root = new B(10, new B(5, new B(3), new B(7)), new B(15, new B(13)));
  // B* root = new B(10, new B(5), new B(15));
  cout << externalPL(root) << endl;
}
