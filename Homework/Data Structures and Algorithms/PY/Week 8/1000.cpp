// 1000. 归并排序
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

template <class Record>
struct Node {
  Record entry;
  Node<Record> *next;
};

template <class Record>
class Sortable_list {
  public:
    Sortable_list();
    ~Sortable_list();
    // 在第position个位置插入值为entry的元素，如果position为0则插入在链表头，以此类推
    // 输入数据中，position满足 0 <= position <= 链表元素数量
    void insert(int position, const Record &entry);
    // 输出链表的内容，每两个元素之间用一个空格隔开，最后一个元素之后没有空格，并且需要换行
    void print();
    // 对链表进行归并排序，你可以添加一些辅助函数，但不能改动类的成员变量
    void merge_sort();
  private:
    Node<Record> *head;                                     // 链表头指针
};

template <class Record>
Sortable_list<Record>::Sortable_list() {
  head = nullptr;
}

template <class Record>
Sortable_list<Record>::~Sortable_list() {
  while (head != nullptr) {
    Node<Record>* tmp = head;
    head = head->next;
    delete tmp;
  }
}

template <class Record>
void Sortable_list<Record>::insert(int position, const Record &entry) {
  if (position == 0) {
    Node<Record>* n = new Node<Record>;
    n->entry = entry;
    n->next = head;
    head = n;
    return;
  }
  Node<Record>* n = head;
  for (int i = 1; i < position; i++) {
    n = n->next;
  }
  Node<Record>* new_n = new Node<Record>;
  new_n->entry = entry;
  new_n->next = n->next;
  n->next = new_n;
}

template <class Record>
void Sortable_list<Record>::print() {
  if (head != nullptr) {
    cout << head->entry;
    for (Node<Record>* it = head->next; it != nullptr; it = it->next) {
      cout << ' ' << it->entry;
    }
  }
  cout << endl;
}

template <class Record>
void Sortable_list<Record>::merge_sort() {
  function<void(vector<Node<Record>*> &v, size_t start, size_t end)> func
  = [&](vector<Node<Record>*> &v, size_t start, size_t end) -> void {
    if (start == end) {
      return;
    }
    //cout << start << " ~ " << end << endl; 
    //print();
    size_t index = (end - start) / 2 + start + 1;
    func(v, start, index - 1);
    func(v, index, end);
    size_t alen = index - start;
    size_t blen = end - index + 1;
    Record arr[alen], brr[blen];
    for (size_t i = 0; i < alen; i++) {
      arr[i] = v[start + i]->entry;
    }
    for (size_t i = 0; i < blen; i++) {
      brr[i] = v[index + i]->entry;
    }
    size_t ai = 0, bi = 0, vi = start;
    while (ai < alen && bi < blen) {
      if (arr[ai] <= brr[bi]) {
        v[vi++]->entry = arr[ai++];
      } else {
        v[vi++]->entry = brr[bi++];
      }
    }
    while (ai < alen) {
      v[vi++]->entry = arr[ai++];
    }
    while (bi < blen) {
      v[vi++]->entry = brr[bi++];
    }
  };
  vector<Node<Record>*> v;
  for (Node<Record>* it = head; it != nullptr; it = it->next) {
    v.push_back(it);
  }
  func(v, 0, v.size() - 1);
}

int main() {
  Sortable_list<int> li;
  for (int i = 0; i < 10; i++) {
    li.insert(0, i);
  }
  li.print();
  li.merge_sort();
  li.print();
}
