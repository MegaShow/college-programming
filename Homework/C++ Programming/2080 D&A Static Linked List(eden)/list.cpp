// MegaShow
#include <sstream>
#include "list.hpp"

list::list(){
    clear();
}

list::list(const list &another){
    *this = another;
}

list& list::operator=(const list & li){
    _size = li._size;
    head = li.head;
    empty_head = li.empty_head;
    for(int i = 0; i < MAX_STORAGE; i++)
        storage[i] = li.storage[i];
    return *this;
}

list::~list(){}

// Capacity
bool list::empty(void) const{
    return _size == 0;
}

list::size_type list::size(void) const{
    return _size;
}

// output
// list: [1,2,3,4,5]
// output: 1->2->3->4->5->NULL
std::string list::toString(void) const{
    std::string str;
    std::string tmp;
    std::stringstream ss;
    pointer p = head;
    while(p != nullpointer){
        ss.clear();
        ss << storage[p].data << "->";
        ss >> tmp;
        str += tmp;
        p = storage[p].next;
    }
    str += "NULL";
    return str;
}

void list::insert(int position, const int &data){
    if(position < 0 || position > _size || _size == MAX_STORAGE)
        return;
    pointer newp = empty_head;
    empty_head = storage[empty_head].next;
    if(position == 0){
        storage[newp].data = data;
        storage[newp].next = head;
        head = newp;
        _size++;
    }
    else{
        pointer p = head;
        for(int i = 1; i < position; i++)
            p = storage[p].next;
        storage[newp].data = data;
        storage[newp].next = storage[p].next;
        storage[p].next = newp;
        _size++;
    }
}

void list::erase(int position){
    if(position < 0 || position >= _size)
        return;
    if(position == 0){
        pointer empty_p = head;
        head = storage[head].next;
        storage[empty_p].next = empty_head;
        empty_head = empty_p;
        _size--;
    }
    else{
        pointer p = head;
        for(int i = 1; i < position; i++)
            p = storage[p].next;
        pointer empty_p = storage[p].next;
        storage[p].next = storage[empty_p].next;
        storage[empty_p].next = empty_head;
        empty_head = empty_p;
        _size--;
    }
}

void list::clear(void){
    _size = 0;
    head = nullpointer;
    empty_head = 0;
    for(int i = 0; i < MAX_STORAGE - 1; i++)
        storage[i].next = i + 1;
    storage[MAX_STORAGE-1].next = nullpointer;
}

list& list::sort(void){
    for(int i = _size; i > 0; i--){
        pointer prev = head;
        pointer next = storage[prev].next;
        for(int j = 1; j < i; j++){
            if(storage[prev].data > storage[next].data){
                data_type var = storage[prev].data;
                storage[prev].data = storage[next].data;
                storage[next].data = var;
            }
            prev = next;
            next = storage[prev].next;
        }
    }
    return *this;
}