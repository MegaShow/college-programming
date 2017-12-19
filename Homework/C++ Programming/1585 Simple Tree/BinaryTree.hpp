// Written by Matrix
#ifndef BT_TREE
#define BT_TREE
#include <iostream>
using namespace std;
struct node {
  int ele;
  node* left;
  node* right;
  node(int e):left(0), right(0){
    ele = e;
  }
};
class BinaryTree {
  private:
    node* root;
    // 此处四个函数均为辅助函数
    static void MemoryDelete(node* p);  // 内存处理的辅助函数
    static void BuildTree(const node* Source_Root, node* &Target_Root);  // 拷贝构造函数的辅助函数
    static void BuildTree(const int* arr,int len, node* &root);  // 数组构建树的辅助函数
    static void preorder(const node* p);    // 输出的辅助函数
  public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree(const int* arr, int len);
    void ResetTree(const int* arr, int len);  // 清空当前树并重置
    ~BinaryTree();
    void clear();  // 清空
    void insert(int ele);  // 按值插入
    void Delete(int ele);  // 暗值删除
    void print();
};
#endif