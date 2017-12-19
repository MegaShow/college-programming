// MegaShow
#include <memory>
#include "base.h"

const std::size_t init_capacity = 10;

template< typename T, typename Alloc = std::allocator<T> >
class myVector : public Base {
  private:
    T* _data;
    std::size_t _capacity;
    std::size_t _size;
  
  public:
  // Constructor
    myVector() : _capacity(init_capacity), _size(0) {
      Alloc a = Alloc();
      _data = a.allocate(_capacity);
    }
    
    myVector(const std::size_t & size, const T & val, Alloc a = Alloc()) : _capacity(size*2), _size(size) {
      _data = a.allocate(_capacity);
      for (std::size_t i = 0; i < size; i++) {
        a.construct(_data + i, val);
      }
    }
    
    template<typename InputIterator>
    myVector(InputIterator begin, InputIterator end, Alloc a = Alloc()) {
      _size = static_cast<std::size_t>(end - begin);
      _capacity = _size * 2;
      _data = a.allocate(_capacity);
      std::size_t t = 0;
      for (InputIterator i = begin; i != end; i++, t++) {
        a.construct(_data + t, *i);
      }
    }
    
    myVector(const myVector & other) : _capacity(other._capacity), _size(other._size) {
      Alloc a = Alloc();
      _data = a.allocate(_capacity);
      for (std::size_t i = 0; i < _size; i++) {
        a.construct(_data + i, other._data[i]);
      }
    }
    
    ~myVector() {
      Alloc a = Alloc();
      for (std::size_t i = 0; i < _size; i++) {
        a.destroy(_data + i);
      }
      a.deallocate(_data, _capacity);
    }
    
    // Copy Operator
    myVector & operator=(const myVector & other) {
      if (&other == this) {
        return *this;
      }
      clear();
      Alloc a = Alloc();
      a.deallocate(_data, _capacity);
      _capacity = other._capacity;
      _size = other._size;
      _data = a.allocate(_capacity);
      for (std::size_t i = 0; i < _size; i++) {
        a.construct(_data + i, other._data[i]);
      }
      return *this;
    }
    
    // Iterator
    typedef T* iterator;
    typedef const T* const_iterator;

    inline iterator begin() {
      return &_data[0];
    }
    
    inline const_iterator begin() const {
      return &_data[0];
    }

    inline iterator end() {
      return &_data[_size];
    }

    inline const_iterator end() const {
      return &_data[_size];
    }

    // Capacity
    inline std::size_t size() {
      return _size;
    }
    
    void resize(const std::size_t & newSize) {
      if (newSize <= _size) {
        Alloc a = Alloc();
        for (std::size_t i = newSize; i < _size; i++) {
          a.destroy(_data + i);
        }
        _size = newSize;
      } else {
        Alloc a = Alloc();
        T* tmp = a.allocate(_capacity);
        for (std::size_t i = 0; i < _size; i++) {
          a.construct(tmp + i, _data[i]);
          a.destroy(_data + i);
        }
        a.deallocate(_data, _capacity);
        _data = tmp;
        for (std::size_t i = _size; i < newSize; i++) {
          a.construct(_data + i, 0);
        }
        _size = newSize;
      }
    }
    
    void resize(const std::size_t & newSize, const T & val) {
      if (newSize <= _size) {
        Alloc a = Alloc();
        for (std::size_t i = newSize; i < _size; i++) {
          a.destroy(_data + i);
        }
        _size = newSize;
      } else {
        Alloc a = Alloc();
        T* tmp = a.allocate(_capacity);
        for (std::size_t i = 0; i < _size; i++) {
          a.construct(tmp + i, _data[i]);
          a.destroy(_data + i);
        }
        a.deallocate(_data, _capacity);
        _data = tmp;
        for (std::size_t i = _size; i < newSize; i++) {
          a.construct(_data + i, val);
        }
        _size = newSize;
      }
    }
    
    inline std::size_t capacity() const {
      return _capacity;
    }

    inline bool empty() const {
      return _size == 0;
    }

    void reserve(const std::size_t & newCapacity) {
      if (newCapacity > _capacity) {
        Alloc a = Alloc();
        T* tmp = a.allocate(newCapacity);
        for (std::size_t i = 0; i < _size; i++) {
          a.construct(tmp + i, _data[i]);
          a.destroy(_data + i);
        }
        a.deallocate(_data, _capacity);
        _capacity = newCapacity;
        _data = tmp;
      }
    }
    
    // Element Access
    inline T & operator[](const std::size_t & index) {
      return _data[index];
    }

    inline const T & operator[](const std::size_t & index) const {
      return _data[index];
    }

    inline T & front() {
      return _data[0];
    }
    
    inline const T & front() const {
      return _data[0];
    }
    
    inline T & back() {
      return _data[_size-1];
    }

    inline const T & back() const {
      return _data[_size-1];
    }

    inline T * data() {
      return _data;
    }

    inline const T * data() const {
      return _data;
    }

    // Modifiers
    template<typename InputIterator>
    void assign(InputIterator begin, InputIterator end) {
      _size = static_cast<std::size_t>(end-begin);
      Alloc a = Alloc();
      std::size_t t = 0;
      for (InputIterator i = begin; i != end; i++, t++) {
        a.construct(_data + t, *i);
      }
    }
    
    void assign(const std::size_t & newSize, const T & val) {
      _size = newSize;
      Alloc a = Alloc();
      for (std::size_t i = 0; i < newSize; i++) {
        a.construct(_data + i, val);
      }
    }
    
    void push_back(const T & val) {
      if (_size == _capacity) {
        reserve(_capacity * 2);
      }
      Alloc a = Alloc();
      a.construct(_data + _size, val);
      _size++;
    }
    
    void pop_back() {
      if (_size == 0) {
        return;
      }
      Alloc a = Alloc();
      _size--;
      a.destroy(_data + _size);
    }
    
    void clear() {
      Alloc a = Alloc();
      for (std::size_t i = 0; i < _size; i++) {
        a.destroy(_data + i);
      }
      _size = 0;
    }
};