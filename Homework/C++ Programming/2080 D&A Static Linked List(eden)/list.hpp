#ifndef LIST_H_
#define LIST_H_
#include <string>
#define MAX_STORAGE 1000
 class list{
    typedef int data_type;
    typedef int pointer;
    typedef unsigned int size_type;
    static const pointer nullpointer = -1;
    typedef struct node {
        data_type data;
        pointer next;
        node(const node &another) {
          this->operator=(another);
        }
        node& operator=(const node &another) {
          this->data = another.data;
          this->next = another.next;
        }
        node(data_type data = 0, pointer next = nullpointer) : data(data), next(next) {}
    } node;
    node storage[MAX_STORAGE];
    size_type _size;
    pointer head;
    pointer empty_head;
 public:
    list();
    list(const list& another);
    list& operator=(const list&);
    ~list();
     // Capacity
    bool empty(void) const;
    size_type size(void) const;
     // output
    // list: [1,2,3,4,5]
    // output: 1->2->3->4->5->NULL
    std::string toString(void) const;
     void insert(int position, const int& data);
    void erase(int position);
    void clear(void);
    list& sort(void);
};
 #endif // !LIST_H_
 