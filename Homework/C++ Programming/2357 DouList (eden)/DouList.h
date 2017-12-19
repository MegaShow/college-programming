#ifndef SSCPP2014_DOULIST_A_H
#define SSCPP2014_DOULIST_A_H
 #include <string>
 struct DouListNode {
  int elem;
  DouListNode *prev, *next;
  DouListNode(int e = 0, DouListNode *p = 0, DouListNode *n = 0) {
    elem = e;
    prev = p;
    next = n;
  }
};
 class DouList {
  private:
    DouListNode *m_head, *m_tail;
  public:
    DouList();
    DouList(const DouList &src);
    ~DouList();
    void clear();
    bool empty() const;
    std::string to_str() const;
    int front() const;
    int back() const;
    void push_front(const int &e);
    void push_back(const int &e);
    void pop_front();
    void pop_back();
    DouList& operator=(const DouList &other);
    friend std::ostream& operator<<(std::ostream &out,
           const DouList &list);
    // non-meaning static value
    static int _error_sign;  // for illegal front()/back()
};
 #endif
 