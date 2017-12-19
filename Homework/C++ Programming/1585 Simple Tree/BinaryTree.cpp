// MegaShow
// [13] Simple Tree
#include <iostream>
#include "BinaryTree.hpp"

// 此处四个函数均为辅助函数

// 内存处理的辅助函数
void BinaryTree::MemoryDelete(node *p){
    if(p->left)
        MemoryDelete(p->left);
    if(p->right)
        MemoryDelete(p->right);
    delete p;
}

// 拷贝构造函数的辅助函数
void BinaryTree::BuildTree(const node *Source_Root, node *&Target_Root){
    if(Source_Root == 0)
        return;
    node* p = new node(Source_Root->ele);
    Target_Root = p;
    BuildTree(Source_Root->left, Target_Root->left);
    BuildTree(Source_Root->right, Target_Root->right);
}

// 数组构建树的辅助函数
void BinaryTree::BuildTree(const int *arr, int len, node *&root){
    for(int i = 0; i < len; i++){
        if(root == 0){
            node* tmp = new node(arr[i]);
            root = tmp;
            continue;
        }
        node* p = root;
        while((p->left && arr[i] < p->ele) || (p->right && p->ele < arr[i])){
            if(arr[i] < p->ele)
                p = p->left;
            else
                p = p->right;
        }
        if(arr[i] < p->ele){
            node* tmp = new node(arr[i]);
            p->left = tmp;
        }
        else if(p->ele < arr[i]){
            node* tmp = new node(arr[i]);
            p->right = tmp;
        }
    }
}

// 输出的辅助函数
void BinaryTree::preorder(const node *p){
    if(p)
        std::cout << p->ele << " ";
    else
        return;
    if(p->left)
        preorder(p->left);
    if(p->right)
        preorder(p->right);
}

BinaryTree::BinaryTree(){
    root = 0;
}

BinaryTree::BinaryTree(const BinaryTree & tree){
    root = 0;
    BuildTree(tree.root, root);
}

BinaryTree::BinaryTree(const int *arr, int len){
    root = 0;
    BuildTree(arr, len, root);
}

// 清空当前树并重置
void BinaryTree::ResetTree(const int *arr, int len){
    clear();
    BuildTree(arr, len, root);
}

BinaryTree::~BinaryTree(){
    clear();
}

// 清空
void BinaryTree::clear(){
    if(root)
        MemoryDelete(root);
    root = 0;
}

// 按值插入
void BinaryTree::insert(int ele){
    BuildTree(&ele, 1, root);
}

// 按值删除
void BinaryTree::Delete(int ele){
    bool angle = 0; // 0=>left, 1=>right;
    node* p_prev = 0;
    node* p = root;
    node* rhs;
    node* rhs_prev = 0;
    // get p_prev, p
    while(p && p->ele != ele){
        p_prev = p;
        if(ele < p->ele){
            p = p->left;
            angle = 0;
        }
        else{
            p = p->right;
            angle = 1;
        }
    }
    // cannot search the ele
    if(p == 0)
        return;
    // delete
    if(p->left){
        rhs = p->left;
        while(rhs->right){
            rhs_prev = rhs;
            rhs = rhs->right;
        }
        if(rhs_prev){
            rhs_prev->right = rhs->left;
            rhs->left = p->left;
            rhs->right = p->right;
        }
        else{
            rhs->right = p->right;
        }
    }
    else
        rhs = p->right;

    if(p_prev && angle)
        p_prev->right = rhs;
    else if(p_prev)
        p_prev->left = rhs;
    else
        root = rhs;
    delete p;
}

void BinaryTree::print(){
    preorder(root);
    std::cout << std::endl;
}