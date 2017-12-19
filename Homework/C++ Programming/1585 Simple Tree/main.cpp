// Written by Matrix
#include "BinaryTree.hpp"
void Test1() {
  BinaryTree t1;
  t1.print();
  int len;
  cin >> len;
  int* arr = new int[len+1];
  int index = 0;
  while (index < len) cin >> arr[index++];
  BinaryTree t2(arr, len);
  t2.print();
  int inser;
  int times;
  cin >> times;
  while (times--) {
    cin >> inser;
    t2.insert(inser);
  }
  t2.print();
  cin >> times;
  int del;
  while (times--) {
    cin >> del;
    t2.Delete(del);
  }
  BinaryTree t3 = t2;
  t3.print();
  t3.clear();
  t3.print();
  t2.print();
  // cout << &t3 << endl;
  // cout << &t2 << endl;
  delete []arr;
}

void Test2() {
  BinaryTree t1;
  t1.Delete(10);
  t1.clear();
  t1.print();
  int times;
  int tmp;
  cin >> times;
  while (times--) {
    cin >> tmp;
    t1.insert(tmp);
  }
  t1.Delete(tmp);
  t1.print();
}
void Test3() {
  int arr[10] = {9,4,3,1,2,10,15,17,18,6};
  BinaryTree t1(arr, 10);
  t1.print();
  arr[9] = 5;
  t1.ResetTree(arr, 10);
  t1.print();
  t1.clear();
  t1.ResetTree(arr, 10);
  t1.print();
}
int main() {
  Test1();
  Test2();
  Test3();
}