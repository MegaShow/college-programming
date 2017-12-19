// MegaShow
#include <sstream>
#include "SimpleList.hpp"

list::list(){
    head = NULL;
    _size = 0;
}

list::list(const list & l){
    head = NULL;
    _size = 0;
    *this = l;
}

list &list::operator=(const list & l){
    clear();
    head = NULL;
    _size = 0;
    node* p = l.head;
    for(int i = 0; i < l._size; i++){
        insert(i, p->data);
        p = p->next;
    }
    return *this;
}

list::~list(){
    clear();
    head = NULL;
    _size = 0;
}

// Capacity
bool list::empty(void) const{
    return _size;
}

int list::size(void) const{
    return _size;
}

std::string list::toString(void) const{
    std::stringstream ss;
    std::string str;
    std::string tmp;
    node* p = head;
    for(int i = 0; i < _size; i++){
        ss.clear();
        ss << p->data;
        ss >> tmp;
        str += (tmp + "->");
        p = p->next;
    }
    str += "NULL";
    return str;
}

void list::insert(int position, const int &data){
    if(position < 0 || position > _size)
        return;
    if(position == 0){
        head = new node(data, head);
        _size++;
    }
    else{
        node* p = head;
        for(int i = 1; i < position; i++)
            p = p->next;
        node* ins = new node(data, p->next);
        p->next = ins;
        _size++;
    }
}

void list::erase(int position){
    if(position < 0 || position >= _size)
        return;
    if(position == 0){
        node* p = head;
        head = head->next;
        delete p;
        _size--;
    }
    else{
        node* p = head;
        for(int i = 1; i < position; i++)
            p = p->next;
        node* ins = p->next;
        p->next = p->next->next;
        delete ins;
        _size--;
    }
}

list& list::sort(void){
    for(int i = 0; i < _size; i++){
        int index = i;
        node* p = head;
        for(int j = 0; j < i; j++)
            p = p->next;
        int min = p->data;
        p = p->next;
        for(int j = i + 1; j < _size; j++){
            if(p->data < min){
                min = p->data;
                index = j;
            }
            p = p->next;
        }
        erase(index);
        insert(i, min);
    }
    return *this;
}