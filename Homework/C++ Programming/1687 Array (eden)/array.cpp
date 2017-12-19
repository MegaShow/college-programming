// MegaShow
#include <algorithm>
#include "array.hpp"


array::array(size_t size){
    _data = new data_type[size];
    _size = size;
}
  
// destructor
array::~array(){
    delete [] _data;
}
  
  // Capacity
  // Return maximum size
array::size_t array::max_size(void){
    return _size;
}
 
  // Element access
  // Access element
  // int& operator[](const int &i) {return data[i];}
  // Access element
array::data_type& array::at(const data_type& i){
    return _data[i];
}
  
  // Access first element
array::data_type& array::front(){
    return _data[0];
}
  
  // Access last element
array::data_type& array::back(){
    return _data[_size-1];
}
  
  // Get pointer to data
array::pointer array::data(){
    return _data;
}
 
  // Modifiers
  // Fill array with the same value
void array::fill(const data_type& value){
    for(int i = 0; i < _size; i++)
        _data[i] = value;
}
  
  // Resize the array (newSize > oldSize)
void array::resize(int newSize){
    pointer p = new data_type[newSize+1];
    for(int i = 0; i < _size; i++)
        p[i] = _data[i];
    delete [] _data;
    _data = p;
    _size = newSize;
}
  
  // Sort the array in the section [from, to)
void array::sort(int from, int to){
    std::sort(_data + from, _data + to);
}