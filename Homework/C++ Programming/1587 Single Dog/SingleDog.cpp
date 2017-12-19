#include <cstring>
#include "SingleDog.h"

int SingleDog::count = 0;

SingleDog::SingleDog(int id_, char* name_) : id(id_){
  count++;
  name = new char[strlen(name_) + 1];
  strcpy(name, name_);
}

//copy constructor
SingleDog::SingleDog(const SingleDog &other) : id(other.id){
  count++;
  name = new char[strlen(other.name) + 1];
  strcpy(name, other.name);
}

//desctructor
SingleDog::~SingleDog(){
  count--;
  delete [] name;
}

//return the count of single dog
int SingleDog::getCount(){
  return count;
}