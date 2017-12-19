#include <iostream>
#include "BinaryTree.hpp"
 
using namespace std;
 
void print(BinaryTree::Node * temp) {
    cout << temp->val << " ";
}
 
std::vector<char> pre;
std::vector<char> in;
 
void getPreOrder(BinaryTree::Node * temp) {
    pre.push_back(temp->val);
}
 
void getInOrder(BinaryTree::Node * temp) {
    in.push_back(temp->val);
}
 
void testTree() {
    cout << "test Tree" << endl;
    int n = 1;
    std::vector<char> tree;
    cin >> n;
    while (n--) {
        char temp = '\0';
        cin >> temp;
        tree.push_back(temp);
    }
 
    BinaryTree x = BinaryTree(tree);
    x = x;
    BinaryTree::preOrder(print, x.getRoot());
    cout << endl;
    BinaryTree::inOrder(print, x.getRoot());
    cout << endl;
    BinaryTree::postOrder(print, x.getRoot());
    cout << endl;
 
    BinaryTree::preOrder(getPreOrder, x.getRoot());
    BinaryTree::inOrder(getInOrder, x.getRoot());
 
    BinaryTree t = BinaryTree(pre, in);
    t = t;
    BinaryTree::postOrder(print, t.getRoot());
    cout << endl;
 
    BinaryTree y = BinaryTree(t);
    y = y;
    BinaryTree::preOrder(print, y.getRoot());
    cout << endl;
    BinaryTree::inOrder(print, y.getRoot());
    cout << endl;
    BinaryTree::postOrder(print, y.getRoot());
 
    BinaryTree::preOrder(getPreOrder, y.getRoot());
    BinaryTree::inOrder(getInOrder, y.getRoot());
}
 
int main() {
    testTree();
}