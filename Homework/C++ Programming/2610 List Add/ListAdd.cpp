// MegaShow
#include <iostream>
#include <string>
#include <sstream>
#include "ListAdd.hpp"
using namespace std;

List::List() {
    _size = 0;
    head = NULL;
}

List::List(const List& other) {
    _size = 0;
    head = NULL;
    *this = other;
}

List::List(const string & num) {
    _size = 0;
    head = NULL;
    for (int i = 0; i < num.size(); i++) {
        push_front(num[i]-'0');
    }
}
    
void List::clear() {
    node* tmp;
    node* p = head; 
    for (int i = 0; i < _size; i++) {
        tmp = p;
        p = p->next;
        delete tmp;
    }
}

void List::push_front(int val) {
    if (head == NULL) {
        head = new node(val);
    } else {
        node* tmp = head;
        head = new node(val, tmp);
    }
    _size++;
}   // 在头部插入数值

List List::operator+(const List& other) {
    List tmp(_size >= other._size ? *this : other);
    List add(_size < other._size ? *this : other);
    node* p = tmp.head;
    node* n = add.head;
    node* prev;
    int var = 0;
    for (int i = 0; i < add._size; i++) {
        //cout << p->val << n->val << endl;
        p->val = p->val + n->val + var;
        var = p->val / 10;
        p->val %= 10;
        prev = p;
        p = p->next;
        n = n->next;
        if (i == add._size - 1 && var != 0) {
            if(p != NULL) {
                while (p != NULL && var != 0) {
                    p->val = p->val + var;
                    var = p->val / 10;
                    p->val %= 10;
                    prev = p;
                    p = p->next;
                }
                if (var != 0) {
                    prev->next = new node(var);
                    tmp._size++;
                }
            } else {
                prev->next = new node(var);
                tmp._size++;
            }
        }
    }
    return tmp;
}    //在这里进行链表加法实现

List& List::operator=(const List& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    _size = other._size;
    node* tmp = other.head;
    node* n, *prev;
    while (tmp != NULL) {
        if(tmp == other.head) {
            head = new node(tmp->val);
            prev = head;
            tmp = tmp->next;
        } else {
            n = new node(tmp->val);
            prev->next = n;
            prev = n;
            tmp = tmp->next;
        }
    }
    return *this;
}   // 赋值操作重载

int List::size() const {
    return _size;
}

List::~List() {
    clear();
}

ostream& operator<<(ostream & os, const List &  out) {
    string str, tmp;
    stringstream ss;
    List::node* p = out.head;
    for (int i = 0; i < out._size; i++) {
        ss.clear();
        ss << p->val;
        ss >> tmp;
        str = tmp + str;
        p = p->next;
    }
    os << str;
    return os;
}
      // 输出数字，无需换行