// MegaShow
#ifndef ZOO_H_
#define ZOO_H_

#include <string>
#include <vector>
#include "animal.h"

class Zoo {
private:
    std::vector<Animal*> mem;
    int count[2];
public:
    Zoo();
    bool addAnimal(Animal *ani);
    int getDogCount();
    int getCatCount();
    bool deleteAnimalByName(std::string _name);
    bool deleteAnimalByAge(int _age);
    void print();
};

#endif
