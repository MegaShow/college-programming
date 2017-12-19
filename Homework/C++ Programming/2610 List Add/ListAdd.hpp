#ifndef _LIST_ADD_
#define _LIST_ADD_

#include <iostream>
using std::string;
using std::ostream;
class List {
  private:
      struct node {
          int val;
          node* next;
          node(int v, node* n = 0):val(v), next(n){}
      };
      node* head;
      int _size;
  public:
      List();
      List(const List& other);
      List(const string & num);
      void clear();
      void push_front(int val);   // 在头部插入数值
      List operator+(const List& other);    //在这里进行链表加法实现
      List& operator=(const List& other);   // 赋值操作重载
      int size() const;
      ~List();
      friend ostream& operator<<(ostream & os, const List &  out);
      // 输出数字，无需换行
};
#endif