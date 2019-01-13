// 1004. AVL Tree
#include <iostream>
using namespace std;

template <class Entry>
class AVL {
 public:
  struct Node {
    Node* left;
    Node* right;
    Entry val;
    int balance_factor;
    Node(Entry v, Node* l = nullptr, Node* r = nullptr): val(v), left(l), right(r) {
      int lbf = left == nullptr ? 0 : left->balance_factor;
      int rbf = right == nullptr ? 0 : right->balance_factor;
      balance_factor = lbf - rbf;
    }
  };
  AVL(): root(nullptr) {}
  bool Insert(const Entry &val);
  void PrintWithPrefix();

 private:
  Node* root;
  bool insert(Node* &subroot, const Entry &val, bool &taller);
  bool left_balance(Node* &subroot);
  bool right_balance(Node* &subroot);
  bool rotate_left(Node* &subroot);
  bool rotate_right(Node* &subroot);
  void printPreOrder(const Node* root);
};

template <class Entry>
void AVL<Entry>::PrintWithPrefix() {
  printPreOrder(root);
  cout << endl;
}

template <class Entry>
void AVL<Entry>::printPreOrder(const Node* n) {
  if (n == nullptr) return;
  cout << n->val << ' ';
  printPreOrder(n->left);
  printPreOrder(n->right);
}

template <class Entry>
bool AVL<Entry>::Insert(const Entry &val) {
  bool taller;
  return insert(root, val, taller);
}

template <class Entry>
bool AVL<Entry>::insert(Node* &subroot, const Entry &val, bool &taller) {
  bool result = true;
  if (subroot == nullptr) {
    subroot = new Node(val);
    taller = true;
  } else if (subroot->val == val) {
    taller = false;
    result = false;
  } else if (val < subroot->val) {
    result = insert(subroot->left, val, taller);
    if (taller) {
      switch (subroot->balance_factor) {
      case 1:
        left_balance(subroot);
        taller = false;
        break;
      case 0:
        subroot->balance_factor = 1;
        break;
      case -1:
        subroot->balance_factor = 0;
        taller = false;
        break;
      }
    }
  } else {
    result = insert(subroot->right, val, taller);
    if (taller) {
      switch (subroot->balance_factor) {
      case 1:
        subroot->balance_factor = 0;
        taller = false;
        break;
      case 0:
        subroot->balance_factor = -1;
        break;
      case -1:
        right_balance(subroot);
        taller = false;
        break;
      }
    }
  }
  return result;
}

template <class Entry>
bool AVL<Entry>::left_balance(Node* &subroot) {
  Node* &left_tree = subroot->left;
  switch (left_tree->balance_factor) {
  case 1:
    subroot->balance_factor = 0;
    left_tree->balance_factor = 0;
    rotate_right(subroot);
    break;
  case 0:
    return false;
  case -1:
    Node* subtree = left_tree->right;
    switch (subtree->balance_factor) {
    case 0:
      subroot->balance_factor = 0;
      left_tree->balance_factor = 0;
      break;
    case -1:
      subroot->balance_factor = 0;
      left_tree->balance_factor = 1;
      break;
    case 1:
      subroot->balance_factor = -1;
      left_tree->balance_factor = 0;
      break;
    }
    subtree->balance_factor = 0;
    rotate_left(left_tree);
    rotate_right(subroot);
    break;
  }
  return true;
}

template <class Entry>
bool AVL<Entry>::right_balance(Node* &subroot) {
  Node* &right_tree = subroot->right;
  switch (right_tree->balance_factor) {
  case -1:
    subroot->balance_factor = 0;
    right_tree->balance_factor = 0;
    rotate_left(subroot);
    break;
  case 0:
    return false;
  case 1:
    Node* subtree = right_tree->left;
    switch (subtree->balance_factor) {
    case 0:
      subroot->balance_factor = 0;
      right_tree->balance_factor = 0;
      break;
    case 1:
      subroot->balance_factor = 0;
      right_tree->balance_factor = -1;
      break;
    case -1:
      subroot->balance_factor = 1;
      right_tree->balance_factor = 0;
      break;
    }
    subtree->balance_factor = 0;
    rotate_right(right_tree);
    rotate_left(subroot);
    break;
  }
  return true;
}

template <class Entry>
bool AVL<Entry>::rotate_left(Node* &subroot) {
  if (subroot == nullptr || subroot->right == nullptr) return false;
  Node* right_tree = subroot->right;
  subroot->right = right_tree->left;
  right_tree->left = subroot;
  subroot = right_tree;
  return true;
}

template <class Entry>
bool AVL<Entry>::rotate_right(Node* &subroot) {
  if (subroot == nullptr || subroot->left == nullptr) return false;
  Node* left_tree = subroot->left;
  subroot->left = left_tree->right;
  left_tree->right = subroot;
  subroot = left_tree;
  return true;
}

int main() {
  int case_num, num, val;
  cin >> case_num;
  while (case_num--) {
    cin >> num;
    AVL<int> tree;
    for (int i = 0; i < num; i++) {
      cin >> val;
      tree.Insert(val);
    }
    tree.PrintWithPrefix();
  }
}

