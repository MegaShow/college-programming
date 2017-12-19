 // MegaShow
#include <iostream>
#include "RHTree.hpp"

RHTree::RHTree() {
	root = NULL;
}

RHTree::~RHTree() {
	if(root)
		funcDelete(root);
}

void RHTree::funcDelete(node* n) {
	if(n->left)
		funcDelete(n->left);
	if(n->right)
		funcDelete(n->right);
	delete n;
}

void RHTree::funcInsert(node* n, int x) {
	if(n->left == NULL && x <= n->data) {
		n->left = new node(x);
		return;
	}
	else if(n->right == NULL && x > n->data) {
		n->right = new node(x);
		return;
	}
	if(x <= n->data)
		funcInsert(n->left, x);
	else
		funcInsert(n->right, x);
}

void RHTree::insert(int x) {
	if(root)
		funcInsert(root, x);
	else
		root = new node(x);
}

RHTree::node* RHTree::getRoot() {
	return root;
}

void RHTree::inOrder(node* _root) {
	if(_root && _root->left)
		inOrder(_root->left);
	if(_root)
		std::cout << " " << _root->data;
	if(_root && _root->right)
		inOrder(_root->right);
}
	
void RHTree::preOrder(node* _root) {
	if(_root)
		std::cout << " " << _root->data;
	if(_root && _root->left)
		preOrder(_root->left);
	if(_root && _root->right)
		preOrder(_root->right);
}

void RHTree::postOrder(node* _root) {
	if(_root && _root->left)
		postOrder(_root->left);
	if(_root && _root->right)
		postOrder(_root->right);
	if(_root)
		std::cout << " " << _root->data;
}
