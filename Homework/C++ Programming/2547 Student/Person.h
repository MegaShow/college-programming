#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person {
public:
 Person(string name, int age) : name(name), age(age) {}
 virtual void sayHi() const {
  cout << "Hi, My name is " << name << ". I'm " << age 
    << " years old." << endl;
 }
 void set(int age) {
  this->age = age;
 }
 void set(string name) {
  this->name = name;
 }
 
private:
 string name;
 int age;
};

#endif