// MegaShow
#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>

enum Type {
    CAT,
    DOG
};

class Animal {
 public:
    Animal(std::string _name, int _age) : name(_name), age(_age) {}
    virtual void Shout() const = 0;
    virtual Type getType() const = 0;
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

 private:
    std::string name;
    int age;
};


class Cat : public Animal {
private:
public:
    Cat() : Animal("", 0) {}
    Cat(const Cat &c) : Animal(c.getName(), c.getAge()) {}
    Cat(std::string _name, int _age) : Animal(_name, _age) {}
    virtual void Shout() const { std::cout << getName() << ": meow~~" << std::endl; }
    virtual Type getType() const { return CAT; }
};


class Dog : public Animal {
private:
public:
    Dog() : Animal("", 0) {}
    Dog(const Dog &d) : Animal(d.getName(), d.getAge()) {}
    Dog(std::string _name, int _age) : Animal(_name, _age) {}
    virtual void Shout() const { std::cout << getName() << ": bark!!" << std::endl; }
    virtual Type getType() const { return DOG; }
};

#endif
