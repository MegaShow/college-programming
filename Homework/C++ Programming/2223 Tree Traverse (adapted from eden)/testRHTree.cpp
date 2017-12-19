#include "RHTree.hpp"
#include <iostream>

int main() {
  int count;
  std::cin >> count;
  int x;
  RHTree tree;
  while (count--) {
    std::cin >> x;
    tree.insert(x);
  }

  std::cout << "Inorder:";
  tree.inOrder(tree.getRoot());
  std::cout << std::endl;
  std::cout << "Preorder:";
  tree.preOrder(tree.getRoot());
  std::cout << std::endl;
  std::cout << "Postorder:";
  tree.postOrder(tree.getRoot());
  std::cout << std::endl;
  return 0;
}