#ifndef LIST
#define LIST

#include <string>
#include <iostream>

class list {
 public:
  typedef int data_type;
  struct node {
   public:
    data_type data;
    node* next;
    node* prev;
    node(data_type data = 0, node* next = NULL, node* prev = NULL)
        : data(data), next(next), prev(prev){};
  };
  typedef node listNode;
  typedef node* listPointer;
  typedef unsigned int size_type;

 private:
  listPointer head;
  listPointer tail;
  size_type _size;
  inline listPointer at(int index) {
    if (index >= 0 && index < this->_size) {
      if (index <= this->_size / 2) {
        int counter = 0;
        listPointer p = this->head;
        while (counter != index) {
          counter++;
          p = p->next;
        }
        return p;
      } else {
        int counter = 0;
        listPointer p = this->tail;
        while (counter != this->_size - 1 - index) {
          counter++;
          p = p->prev;
        }
        return p;
      }
    }
    return NULL;
  }

 public:
  list();
  // construct a list from an exist array
  list(const data_type[], int length);
  list(const list&);
  list& operator=(const list&);
  ~list();

  // Capacity
  bool empty(void) const;
  size_type size(void) const;

  // Element access
  data_type& front(void) const;
  data_type& back(void) const;

 public:
  // output
  std::string toString(void) const;

  // Modifiers
  void assign(const list&);
  void assign(const data_type datas[], int length);
  void push_front(const data_type&);
  void push_back(const data_type&);
  void pop_front(void);
  void pop_back(void);

  void insert(int position, const data_type& data);
  void erase(int position);
  void clear(void);

  // Operations
  // split this list into to lists at the given position
  void split(int position, list* des1, list* dest2);
  // merge two list to this list from src1 and src2
  list& merge(const list& src1, const list& src2);
  // remove the elements who satisfy the condition
  list& remove_if(bool (*condition)(listPointer));

  // remove duplicate elements
  list& unique(void);
  // reverse the list
  list& reverse(void);

  // operators
  data_type& operator[](int index);
  list& operator+=(const list&);
  friend std::ostream& operator<<(std::ostream& os, const list& li);
};

#endif

