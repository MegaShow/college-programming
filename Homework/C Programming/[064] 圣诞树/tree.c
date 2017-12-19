/*
 *	Name: [064] 圣诞树
 *	Author: Mega Show
 *	Date: 2017.1.12
 */

#include <stdlib.h>
#include "tree.h"

Node* init_root(int value){
    return create_node(value);
}

Node* create_node(int value){
    Node* root = (Node*)malloc(sizeof(Node));
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void insert_node(Node *p, int value){
    if(p->left == NULL && value < p->value)
        p->left = create_node(value);
    else if(p->right == NULL && value > p->value)
        p->right = create_node(value);
    else if(p->left != NULL && value < p->value)
        insert_node(p->left, value);
    else if(p->right != NULL && value > p->value)
        insert_node(p->right, value);
}

void traverse_tree_inorder(Node *p){
    if(p != NULL){
        traverse_tree_inorder(p->left);
        printf("%d ", p->value);
        traverse_tree_inorder(p->right);
    }
}

void recycle_nodes(Node *p){
    if(p != NULL){
        recycle_nodes(p->left);
        recycle_nodes(p->right);
        free(p);
    }
}
