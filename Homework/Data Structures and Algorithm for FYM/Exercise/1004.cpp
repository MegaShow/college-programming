// 1004. Hashing
#include <algorithm>
#include <vector>
#include <list>
using std::list;
using std::find;
using std::vector;

#define hash Hash

bool isPrime(int n) {
  if(n == 2 || n == 3)
    return true;
  if(n == 1 || n % 2 == 0)
    return false;
  for(int i = 3; i * i <= n; i += 2)
    if(n % i == 0)
      return false;
  return true;
}

int nextPrime(int n) {
  if(n % 2 == 0)
    n++;
  for( ; !isPrime(n); n += 2)
    ;
  return n;
}

template <typename HashedObj>
class HashTable {
 public:
  HashTable(int (*h)(HashedObj x), int size = 101) :currentSize(0), hash(h) {
    theLists.resize(size);
  }

  // If x is in the table, it returns true, otherwise, it returns false.
  bool contains(const HashedObj & x) const {
    int index = myhash(hash(x));
    auto it = find(theLists[index].begin(), theLists[index].end(), x);
    return it != theLists[index].end();
  }

  void makeEmpty() {
    for(int i = 0; i < theLists.size(); i++)
      theLists[i].clear();
  }

  //Insert key x  if x is not in the table and return true. Otherwise, return false and do nothing.  If the table is full, you will call rehash.
  bool insert(const HashedObj &x) {
    int index = myhash(hash(x));
    auto it = find(theLists[index].begin(), theLists[index].end(), x);
    if (it != theLists[index].end()) return false;
    theLists[index].push_back(x);
    currentSize++;
    if (currentSize == theLists.size()) rehash();
    return true;
  }

  //If x is present in the table, remove it and return true. Otherwise, return false.
  bool remove(const HashedObj &x) {
    int index = myhash(hash(x));
    auto it = find(theLists[index].begin(), theLists[index].end(), x);
    if (it == theLists[index].end()) return false;
    theLists[index].erase(it);
    currentSize--;
    return true;
  }

 private:
  vector<list<HashedObj> > theLists;   // The array of Lists
  int currentSize;
  int (*hash)(HashedObj x); //hash function

  int myhash(const HashedObj &x) const {
    int hashVal = hash(x);
    hashVal %= theLists.size();
    if(hashVal < 0)
      hashVal += theLists.size();
    return hashVal;
  }

  void rehash() {
    vector<list<HashedObj> > oldLists = theLists;
    // Create new double-sized, empty table
    theLists.resize(nextPrime(2 * theLists.size()));
    for(int j = 0; j < theLists.size(); j++)
      theLists[j].clear();
    // Copy table over
    currentSize = 0;
    for(int i = 0; i < oldLists.size(); i++) {
      auto itr = oldLists[i].begin();
      while(itr != oldLists[i].end())
        insert(*itr++);
    }
  }
};

int main() {}
