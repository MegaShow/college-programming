// MegaShow
#include <string>
#include <iostream>
using std::cout;
using std::endl;

class Object {
public:
    virtual std::string obj() const { return "Object"; }
};

class Animal : public Object {
public:
    virtual std::string obj() const { return "Animal"; }
};

class Vehicle : public Object {
public:
    virtual std::string obj() const { return "Vehicle"; }
};

class Dog : public Animal {
public:
    virtual std::string obj() const { return "Dog"; }
};

class Cat : public Animal {
public:
    virtual std::string obj() const { return "Cat"; }
};

class Bus : public Vehicle {
public:
    virtual std::string obj() const { return "Bus"; }
};

class Car : public Vehicle {
public:
    virtual std::string obj() const { return "Car"; }
};


std:: string instanceOf(const Object* obj) {
    if(obj == NULL)
        return "NULL";
    else
        return obj->obj();
}

