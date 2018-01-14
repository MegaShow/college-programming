// 1156. Binary tree
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

struct BinaryTree {
  char val;
  BinaryTree* left;
  BinaryTree* right;
  BinaryTree() :val(0), left(NULL), right(NULL) {}
};

void PreOrder(BinaryTree* root, void (*func)(char));

int main() {
  int node_num;
  while (cin >> node_num) {
    map<int, BinaryTree*> m;
    set<int> root_set;
    set<int> lr_set;
    vector<int> v(1);
    for (int i = 0; i < node_num; i++) {
      int id, left, right;
      char val;
      cin >> id >> val >> left >> right;
      if (left && !m.count(left)) m.insert({ left, new BinaryTree() });
      if (right && !m.count(right)) m.insert({ right, new BinaryTree() });
      if (!m.count(id)) m.insert({ id, new BinaryTree() });
      BinaryTree* node = m[id];
      node->val = val;
      if (left) node->left = m[left];
      if (right) node->right = m[right];
      root_set.insert(id);
      lr_set.insert(left);
      lr_set.insert(right);
    }
    set_difference(root_set.begin(), root_set.end(), lr_set.begin(), lr_set.end(), v.begin());
    // cout << "Root = " << *v.begin() << endl;
    PreOrder(m[*v.begin()], [](char c) -> void { cout << c; });
    cout << endl;
    for (auto &i: m) {
      delete i.second;
    }
  }
}

void PreOrder(BinaryTree* root, void (*func)(char)) {
  if (root != NULL) {
    func(root->val);
    PreOrder(root->left, func);
    PreOrder(root->right, func);
  }
}
