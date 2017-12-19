// MegaShow
#include <functional>
#include "BinaryTree.hpp"

BinaryTree::BinaryTree(const BinaryTree &t) {
    root = NULL;
    *this = t;
}

BinaryTree::BinaryTree(std::vector<char> &arr) {
    root = NULL;
    std::queue<Node*> nq;
    if(arr.size() && arr[0] != '#') {
        root = new Node(arr[0]);
        nq.push(root);
    }
    for(int i = 1; nq.size() && i < arr.size(); i++) {
        Node* n = nq.front();
        nq.pop();
        if(arr[i] != '#') {
            n->left = new Node(arr[i]);
            nq.push(n->left);
        }
        i++;
        if(i < arr.size() && arr[i] != '#') {
            n->right = new Node(arr[i]);
            nq.push(n->right);
        }
    }
}

void function_xxxxxxxx(const std::vector<char> &preOrder, const std::vector<char> &inOrder, BinaryTree::Node* root) {
    root->val = preOrder[0];
    if(preOrder.size() == 1) {
        return;
    }
    std::vector<char> lhsPre, lhsIn, rhsPre, rhsIn;
    int i = 0;
    while(inOrder[i] != root->val) {
        lhsPre.push_back(preOrder[i+1]);
        lhsIn.push_back(inOrder[i]);
        i++;
    }
    for(i++; i < inOrder.size(); i++) {
        rhsPre.push_back(preOrder[i]);
        rhsIn.push_back(inOrder[i]);
    }
    if(lhsPre.size()) {
        root->left = new BinaryTree::Node('#');
        function_xxxxxxxx(lhsPre, lhsIn, root->left);
    }
    if(rhsPre.size()) {
        root->right = new BinaryTree::Node('#');
        function_xxxxxxxx(rhsPre, rhsIn, root->right);
    }
}

// created by preorder and inorder
BinaryTree::BinaryTree(const std::vector<char> &preOrder, const std::vector<char> &inOrder) {
    root = NULL;
    if(preOrder.size()) {
        root = new Node('#');
        function_xxxxxxxx(preOrder, inOrder, root);
    }
}

BinaryTree::~BinaryTree() {
    clear();
}

BinaryTree &BinaryTree::operator=(const BinaryTree &t) {
    if(this == &t)
        return *this;
    clear();
    root = copyNode(t.root, NULL);
    return *this;
}

BinaryTree::Node *BinaryTree::getRoot() const {
    return root;
}

void BinaryTree::clear() {
    postOrder([](BinaryTree::Node* n){delete n;}, root);
    root = NULL;
}

void BinaryTree::preOrder(void (*visite)(BinaryTree::Node *), Node * n) {
    if(n != NULL) {
        visite(n);
        preOrder(visite, n->left);
        preOrder(visite, n->right);
    }
}

void BinaryTree::inOrder(void (*visite)(BinaryTree::Node *), Node * n) {
    if(n != NULL) {
        inOrder(visite, n->left);
        visite(n);
        inOrder(visite, n->right);
    }
}

void BinaryTree::postOrder(void (*visite)(BinaryTree::Node *), Node * n) {
    if(n != NULL) {
        postOrder(visite, n->left);
        postOrder(visite, n->right);
        visite(n);
    }
}


BinaryTree::Node *BinaryTree::copyNode(Node *oldNode, Node *newNode) {
    if(oldNode == NULL)
        return NULL;
    newNode = new Node(oldNode->val);
    newNode->left = copyNode(oldNode->left, NULL);
    newNode->right = copyNode(oldNode->right, NULL);
    return newNode;
}
