
#include <iostream>
#include <cstdlib>
#include "Collection.hpp"
#include "List.hpp"
#include "LinkedList.hpp"
#include "ArrayList.hpp"
#include <exception>
#include <cstdlib>
#include <ctime>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::exception;

class AlgorithmnForbidden : public exception {
  virtual const char *what() const throw() {
    return "Please do not use std::sort or std::list or std::vector .....";
  }
};

class TEST {
 private:
  int *testData;
  int data_size;

 public:
  TEST() {
#if defined(_GLIBCXX_ALGORITHM) || defined(_GLIBCXX_LIST) || \
    defined(_GLIBCXX_VECTOR)
    //throw AlgorithmnForbidden();
    cout << "please do not use algorithm" << endl;
#endif
    cin >> data_size;
    cout << "test data size:" << data_size << endl;
    testData = new int[data_size];
    for (int i = 0; i < data_size; i++) {
      cin >> testData[i];
    }
  }

  ~TEST() { delete[] testData; }

  void test_List(Collection *c) {
    cout << (c->isEmpty() ? "true" : "false") << endl;

    int n = data_size;

    for (int i = 0; i < n; i++) {
      c->add(testData[i]);
    }

    reinterpret_cast<List *>(c)->sort();

    for (int i = 0; i < n; i++) {
      cout << (*reinterpret_cast<List *>(c))[i] << " ";
    }

    cout << endl;

    // not empty
    cout << (c->isEmpty() ? "true" : "false") << endl;

    for (int i = 0; i < n / 2; i++) {
      cout << "(" << (c->contain(i) ? "true" : "false");
      cout << ","
           << (reinterpret_cast<List *>(c)->indexOf(i) != -1 ? "true" : "false")
           << ") ";
      c->remove(i);
    }

    cout << endl;

    for (int i = 0; i < c->size(); i++) {
      cout << (*reinterpret_cast<List *>(c))[i] << " ";
    }
    cout << endl;
  }

  void test_ArrayList() {
    Collection *c = new ArrayList();
    test_List(c);
    delete c;
  }

  void test_LinkedList() {
    Collection *c = new LinkedList();
    test_List(c);
    delete c;
  }

  void runAllTests() {
    clock_t t1, t2;
    t1 = clock();
    cout << "Testing ArrayList:" << endl;
    test_ArrayList();
    t2 = clock();
    cout << endl;
    double temp1 = (double)(t2 - t1)/ CLOCKS_PER_SEC;
    cout << "Testing LinkedList:" << endl;
    test_LinkedList();
    t1 = clock();
    cout << temp1 << endl;
    cout << (double)(t1 - t2)/ CLOCKS_PER_SEC << endl;
  }
};

int main() {
  TEST t;
  t.runAllTests();
  int tem;
  cin >> tem;
  return 0;
}
