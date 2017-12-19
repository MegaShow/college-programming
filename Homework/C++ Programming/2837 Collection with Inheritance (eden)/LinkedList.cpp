// MegaShow
#include "LinkedList.hpp"

LinkedList::LinkedList() {
    head = tail = NULL;
    _size = 0;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::add(E e) {
    if (tail == NULL) {
        head = tail = new node(e);
    } else {
        tail = new node(e, NULL, tail);
        tail->prev->next = tail;
    }
    _size++;
}

void LinkedList::clear(void) {
    while (head) {
        node* tmp = head;
        head = head->next;
        delete tmp;
    }
    head = tail = NULL;
    _size = 0;
}

bool LinkedList::contain(E e) {
    for (node* n = head; n; n = n->next) {
        if (n->data == e) {
            return true;
        }
    }
    return false;
}

bool LinkedList::isEmpty(void) {
    return _size == 0;
}

void LinkedList::remove(E e) {
    node* n = head;
    while (n) {
        if (n->data == e) {
            if (n->next) {
                n->next->prev = n->prev;
            } else {
                tail = n->prev;
            }
            if (n->prev) {
                n->prev->next = n->next;
            } else {
                head = n->next;
            }
            node* tmp = n;
            n = n->next;
            delete tmp;
            _size--;
        } else {
            n = n->next;
        }
    }
}

E& LinkedList::operator[](int index) {
    node* n = head;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }
    return n->data;
}

E& LinkedList::get(int index) {
    node* n = head;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }
    return n->data;
}

int LinkedList::indexOf(E element) {
    node* n = head;
    for (int i = 0; i < _size; i++) {
        if (n->data == element) {
            return i;
        }
        n = n->next;
    }
    return -1;
}

void LinkedList::sort(void) {
    struct list {
        node* head;
        node* tail;
        int size;
        list(node* _head, node* _tail, int _size)
            : head(_head), tail(_tail), size(_size) {}
        void sort() {
            if (size > 1) {
                node* li2head = head;
                for (int i = 0; i < size / 2; i++) {
                    li2head = li2head->next;
                }
                list li1(head, li2head->prev, size / 2);
                list li2(li2head, tail, size - size / 2);
                li1.sort();
                li2.sort(); 
                merge(li1, li2);
                head->prev = tail->next = NULL;
            }
        }
        void merge(const list& li1, const list& li2) {
            node* n;
            node* n1 = li1.head;
            node* n2 = li2.head;
            int i1 = 0, i2 = 0;
            if (n1->data <= n2->data) {
                n = head = n1;
                n1 = n1->next;
                i1++;
            } else {
                n = head = n2;
                n2 = n2->next;
                i2++;
            }
            while (i1 < li1.size && i2 < li2.size) {
                if (n1->data <= n2->data) {
                    n->next = n1;
                    n1->prev = n;
                    n1 = n1->next;
                    i1++;
                } else {
                    n->next = n2;
                    n2->prev = n;
                    n2 = n2->next;
                    i2++;
                }
                n = n->next;
            }
            if (i1 < li1.size) {
                n->next = n1;
                n1->prev = n;
                tail = li1.tail;
            }
            if (i2 < li2.size) {
                n->next = n2;
                n2->prev = n;
                tail = li2.tail;
            }
        }
    };
    list li(head, tail, _size);
    li.sort();
    head = li.head;
    tail = li.tail;
}

int LinkedList::size(void) {
    return _size;
}
