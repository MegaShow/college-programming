// MegaShow
#include <sstream>
#include "List.hpp"



list::list(){
    head = NULL;
    tail = NULL;
    _size = 0;
}


// construct a list from an exist array
list::list(const data_type arr[], int length){
    head = NULL;
    tail = NULL;
    _size = 0;
    assign(arr, length);
}


list::list(const list& li){
    head = NULL;
    tail = NULL;
    _size = 0;
    assign(li);
}


list& list::operator=(const list& li){
    list tmp;
    tmp.assign(li);
    assign(tmp);
    return *this;
}


list::~list(){
    clear();
}


// Capacity
bool list::empty(void) const{
    return _size == 0;
}


list::size_type list::size(void) const{
    return _size;
}


// Element access
list::data_type& list::front(void) const{
    return head->data;
}


list::data_type& list::back(void) const{
    return tail->data;
}


// output
std::string list::toString(void) const{
    std::stringstream ss;
    std::string str;
    if(_size){
        list::listPointer p = head;
        ss << "NULL<-" << p->data;
        while(p->next){
            p = p->next;
            ss << "<->" << p->data;
        }
        ss << "->NULL" << std::endl;
    }
    else
        ss << "NULL" << std::endl;
    ss >> str;
    return str;
}


// Modifiers
void list::assign(const list& li){
    clear();
    listPointer p = li.head;
    for(int i = 0; i < li._size; i++){
        push_back(p->data);
        p = p->next;
    }
}


void list::assign(const data_type datas[], int length){
    clear();
    for(int i = 0; i < length; i++){
        push_back(datas[i]);
    }
}


void list::push_front(const data_type& var){
    if(head == NULL){
        head = new listNode(var, NULL, NULL);
        tail = head;
    }
    else{
        listPointer p = new listNode(var, head, NULL);
        head->prev = p;
        head = p;
    }
    _size++;
}


void list::push_back(const data_type& var){
    if(tail == NULL){
        tail = new listNode(var, NULL, NULL);
        head = tail;
    }
    else{
        listPointer p = new listNode(var, NULL, tail);
        tail->next = p;
        tail = p;
    }
    _size++;
}


void list::pop_front(void){
    if(head == NULL)
        return;
    listPointer p = head;
    head = head->next;
    if(head)
        head->prev = NULL;
    else
        tail = NULL;
    delete p;
    _size--;
}


void list::pop_back(void){
    if(tail == NULL)
        return;
    listPointer p = tail;
    tail = tail->prev;
    if(tail)
        tail->next = NULL;
    else
        head = NULL;
    delete p;
    _size--;
}


void list::insert(int position, const data_type& data){
    if(position < 0 || position > _size)
        return;
    if(position == 0)
        push_front(data);
    else if(position == _size)
        push_back(data);
    else if(position <= _size / 2){
        listPointer prev = NULL;
        listPointer p = head;
        for(int i = 0; i < position; i++){
            prev = p;
            p = p->next;
        }
        listPointer newl = new listNode(data, p, prev);
        prev->next = newl;
        p->prev = newl;
        _size++;
    }
    else{
        listPointer next = NULL;
        listPointer p = tail;
        for(int i = position; i < _size; i++){
            next = p;
            p = p->prev;
        }
        listPointer newl = new listNode(data, next, p);
        next->prev = newl;
        p->next = newl;
        _size++;
    }
}


void list::erase(int position){
    if(position < 0 || position >= _size)
        return;
    if(position == 0)
        pop_front();
    else if(position == _size - 1)
        pop_back();
    else if(position <= _size / 2){
        listPointer p = head;
        for(int i = 0; i < position; i++)
            p = p->next;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        _size--;
    }
    else{
        listPointer p = tail;
        for(int i = position + 1; i < _size; i++)
            p = p->prev;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        _size--;
    }
}


void list::clear(void){
    listPointer p = head;
    listPointer tmp = NULL;
    for(int i = 0; i < _size; i++){
        tmp = p;
        p = p->next;
        delete tmp;
    }
    head = tail = NULL;
    _size = 0;
}


// Operations
// split this list into to lists at the given position
void list::split(int position, list* dest1, list* dest2){
    dest1->clear();
    dest2->clear();
    listPointer p = head;
    for(int i = 0; i < position; i++){
        dest1->push_back(p->data);
        p = p->next;
    }
    for(int i = position; i < _size; i++){
        dest2->push_back(p->data);
        p = p->next;
    }
}


// merge two list to this list from src1 and src2
list& list::merge(const list& src1, const list& src2){
    list tmp = src2;
    *this = src1;
    *this += tmp;
    return *this;
}


// remove the elements who satisfy the condition
list& list::remove_if(bool (*condition)(listPointer)){
    listPointer p = head;
    while(p != NULL){
        if(condition(p)){
            if(p == head){
                p = p->next;
                pop_front();
            }
            else if(p == tail){
                p = NULL;
                pop_back();
            }
            else{
                listPointer tmp = p;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                p = p->next;
                delete tmp;
                _size--;
            }
        }
        else
            p = p->next;
    }
    return *this;
}


// remove duplicate elements
list& list::unique(void){
    data_type* arr = new data_type[_size];
    int arr_size = 0;
    listPointer p = head;
    while(p != NULL){
        bool flag = false;
        for(int i = 0; i < arr_size; i++){
            if(arr[i] == p->data)
                flag = true;
        }
        if(flag){
            if(p == head){
                p = p->next;
                pop_front();
            }
            else if(p == tail){
                p = NULL;
                pop_back();
            }
            else{
                listPointer tmp = p;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                p = p->next;
                delete tmp;
                _size--;
            }
        }
        else{
            arr[arr_size++] = p->data;
            p = p->next;
        }
    }
    delete [] arr;
    return *this;
}


// reverse the list
list& list::reverse(void){
    listPointer p = head;
    listPointer tmp;
    for(int i = 0; i < _size; i++){
        tmp = p->next;
        p->next = p->prev;
        p->prev = tmp;
    }
    tmp = head;
    head = tail;
    tail = tmp;
    return *this;
}


// operators
list::data_type& list::operator[](int index){
    return at(index)->data;
}


list& list::operator+=(const list& li){
    listPointer p = li.head;
    for(int i = 0; i < li._size; i++){
        push_back(p->data);
        p = p->next;
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const list& li){
    os << li.toString();
    return os;
}
