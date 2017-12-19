 // MegaShow
#ifndef RHTREE_HPP_
#define RHTREE_HPP_


class RHTree {
private:
	struct node {
		int data;
		node* left;
		node* right;
		node(int _data = 0, node* _left = 0, node* _right = 0) {
			data = _data;
			left = _left;
			right = _right;
		}
	};
	node* root;
	static void funcDelete(node* n);
	static void funcInsert(node* n, int x);
public:
	RHTree();
	~RHTree();
	void insert(int x);
	node* getRoot();
	void inOrder(node* _root);
	void preOrder(node* _root);
	void postOrder(node* _root);
};

#endif