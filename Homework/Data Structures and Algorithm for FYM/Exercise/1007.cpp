// 1007. Find the middle element in a Linked List
#include <cstdio>

template <typename Node_entry>
struct Node {
  Node_entry entry;
  Node *next;
  Node();
  Node(Node_entry item, Node *add_on = NULL);
};

template <typename Node_entry>
Node<Node_entry>::Node() {
  next = NULL;
}

template <typename Node_entry>
Node<Node_entry>::Node(Node_entry item, Node *add_on) {
  entry = item;
  next = add_on;
}

#include <vector>
#include <cstdio>
using namespace std;

template<typename T>
const Node<T>* medianElement(const Node<T>* head) {
  if (head == NULL) return NULL;
  vector<const Node<T>*> v;
  while (head) {
    v.push_back(head);
    head = head->next;
  }
  return v[(v.size() - 1) / 2];
}

#include <iostream>
using namespace std;
int main() {
  Node<int>* root = new Node<int>(3, new Node<int>(4, new Node<int>(8, new Node<int>(9))));
  cout << medianElement(root)->entry << endl;
}
