// 1000. HashTable
#include <vector>
#include <algorithm>
using namespace std;
// 按线性探查法解决冲突。
template <typename Key, typename Value>
class HashTable {
  struct Pair {
    bool isEmpty;
    Key key;
    Value value;
    Pair() {
      isEmpty = true;
    }
  };

 private:
  Pair * storage;
  int capacity;
  int count;

 public:
  HashTable(int size = 10) {
    capacity = size;
    storage = new Pair[capacity];
    count = 0;
  }

  ~HashTable() {
    delete [] storage;
  }

  void clear() {
    delete [] storage;
    storage = new Pair[capacity];
    count = 0;
  }

  int size() const {
    return count;
  }

  vector<Key> getKeys() const {
    vector<Key> keys;
    for (int i = 0; i < capacity; ++ i) {
      if (storage[i].isEmpty) continue;
      keys.push_back(storage[i].key);
    }
    return keys;
  }

// TODO: You should just submit the function, not the class or the main function.
  HashTable(const HashTable & table);
  HashTable & operator = (const HashTable & table);
  bool hasKey(const Key & key) const;
  const Value & get(const Key & key) const;
  void put(const Key & key, const Value & value);
};



template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &table) {
  capacity = table.capacity;
  count = table.count;
  storage = new Pair[capacity];
  for (int i = 0; i < capacity; i++) {
    storage[i].isEmpty = table.storage[i].isEmpty;
    if (storage[i].isEmpty == false) {
      storage[i].key = table.storage[i].key;
      storage[i].value = table.storage[i].value;
    }
  }
}

template <typename Key, typename Value>
HashTable<Key, Value>& HashTable<Key, Value>::operator=(const HashTable &table) {
  delete [] storage;
  capacity = table.capacity;
  count = table.count;
  storage = new Pair[capacity];
  for (int i = 0; i < capacity; i++) {
    storage[i].isEmpty = table.storage[i].isEmpty;
    if (storage[i].isEmpty == false) {
      storage[i].key = table.storage[i].key;
      storage[i].value = table.storage[i].value;
    }
  }
  return *this;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::hasKey(const Key &key) const {
  vector<Key> v = getKeys();
  return find(v.begin(), v.end(), key) != v.end();
}

template <typename Key, typename Value>
const Value& HashTable<Key, Value>::get(const Key & key) const {
  if (hasKey(key)) {
    for (int i = 0; i < capacity; i++) {
      if (storage[i].isEmpty == false && storage[i].key == key) {
        return storage[i].value;
      }
    }
  } else {
    return 0;
  }
}

template <typename Key, typename Value>
void HashTable<Key, Value>::put(const Key & key, const Value & value) {
  if (hasKey(key)) {
    for (int i = 0; i < capacity; i++) {
      if (storage[i].isEmpty == false && storage[i].key == key) {
        storage[i].value = value;
        return;
      }
    }
  } else {
    if (capacity == count) {
      Pair* tmp = storage;
      capacity *= 2;
      count = 0;
      storage = new Pair[capacity];
      for (int i = 0; i < capacity / 2; i++) {
        if (tmp[i].isEmpty == false) {
          put(tmp[i].key, tmp[i].value);
        }
      }
      delete [] tmp;
    }
    int index = key % capacity;
    while (storage[index].isEmpty == false) {
      index++;
      if (index == capacity) index = 0;
    }
    if (storage[index].isEmpty) {
      storage[index].isEmpty = false;
      storage[index].key = key;
      storage[index].value = value;
      count++;
    }
  }
}

int main() {}
