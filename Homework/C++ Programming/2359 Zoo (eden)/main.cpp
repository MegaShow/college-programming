#include <iostream>
#include <string>
#include "animal.h"
#include "zoo.h"
using namespace std;
 
int main() {
 
    Dog dogs[10];
    Cat cats[10];
    Zoo zoo;
 
    int cnt1, cnt2;
    string name;
    int age;
 
    cin >> cnt1 >> cnt2;
    for (int i = 0; i < cnt1; i++) {
        cin >> name >> age;
        dogs[i] = Dog(name, age);
        zoo.addAnimal(&dogs[i]);
    }
    for (int i = 0; i < cnt2; i++) {
        cin >> name >> age;
        cats[i] = Cat(name, age);
        zoo.addAnimal(&cats[i]);
    }
 
    std::cout << zoo.getDogCount() << std::endl;
    std::cout << zoo.getCatCount() << std::endl;
 
    cin >> name;  // specified name to delete.
    cin >> age;   // specified age to delete.
    zoo.deleteAnimalByName(name);
    zoo.deleteAnimalByAge(age);
 
    std::cout << zoo.getDogCount() << std::endl;
    std::cout << zoo.getCatCount() << std::endl;
 
    zoo.print();
 
    return 0;
}