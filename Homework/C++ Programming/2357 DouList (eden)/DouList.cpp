// MegaShow
#include <string>
#include <sstream>
#include "DouList.h"

int DouList::_error_sign = 0; // for illegal front()/back()

DouList::DouList() {
    m_head = m_tail = 0;
}

DouList::DouList(const DouList &src) {
    m_head = m_tail = 0;
    *this = src;
}

DouList::~DouList() {
    clear();
}

void DouList::clear() {
    while(m_head) {
        pop_back();
    }
    m_head = m_tail = 0;
}

bool DouList::empty() const {
    return m_head == 0;
}

std::string DouList::to_str() const {
    std::stringstream ss;
    std::string str = "[";
    std::string tmp;
    DouListNode* p = m_head;
    if(p) {
        ss << p->elem;
        ss >> tmp;
        str += tmp;
        p = p->next;
    }
    while(p) {
        ss.clear();
        ss << p->elem;
        ss >> tmp;
        str += ", ";
        str += tmp;
        p = p->next;      
    }
    str += "]";
    return str;
}

int DouList::front() const {
    if(m_head)
        return m_head->elem;
    return _error_sign;
}

int DouList::back() const {
    if(m_tail)
        return m_tail->elem;
    return _error_sign;
}

void DouList::push_front(const int &e) {
    if(m_head == 0) {
        m_head = new DouListNode(e);
        m_tail = m_head;
    }
    else {
        DouListNode* n = new DouListNode(e, 0, m_head);
        m_head->prev = n;
        m_head = n;
    }
}

void DouList::push_back(const int &e) {
    if(m_tail == 0) {
        m_tail = new DouListNode(e);
        m_head = m_tail;
    }
    else {
        DouListNode* n = new DouListNode(e, m_tail, 0);
        m_tail->next = n;
        m_tail = n;
    }
}

void DouList::pop_front() {
    if(m_head == 0)
        return;
    if(m_head->next == 0) {
        delete m_head;
        m_head = m_tail = 0;
    }
    else {
        DouListNode* tmp = m_head;
        m_head = m_head->next;
        m_head->prev = 0;
        delete tmp;
    }
}

void DouList::pop_back() {
    if(m_tail == 0)
        return;
    if(m_tail->prev == 0) {
        delete m_tail;
        m_tail = m_head = 0;
    }
    else {
        DouListNode* tmp = m_tail;
        m_tail = m_tail->prev;
        m_tail->next = 0;
        delete tmp;
    }
}

DouList &DouList::operator=(const DouList &other) {
    if(this == &other)
        return *this;
    clear();
    for(DouListNode* p = other.m_head; p; p = p->next) {
        push_back(p->elem);
    }
}

std::ostream &operator<<(std::ostream &out, const DouList &list) {
    out << list.to_str();
    return out;
}
