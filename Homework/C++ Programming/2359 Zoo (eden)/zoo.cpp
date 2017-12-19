// MegaShow
#include <iostream>
#include "zoo.h"

Zoo::Zoo() {
    count[DOG] = 0;
    count[CAT] = 0;
}

bool Zoo::addAnimal(Animal *ani) {
    for(int i = 0; i < mem.size(); i++) {
        if(mem[i] == ani)
            return false;
    }
    count[ani->getType()]++;
    mem.push_back(ani);
    return true;
}

int Zoo::getDogCount() {
    return count[DOG];
}

int Zoo::getCatCount() {
    return count[CAT];
}

bool Zoo::deleteAnimalByName(std::string _name) {
    int dbool = 0;
    for(std::vector<Animal*>::iterator it = mem.begin(); it != mem.end(); it++) {
        if((*it)->getName() == _name) {
            count[(*it)->getType()]--;
            std::vector<Animal*>::iterator tmp = it;
            it--;
            mem.erase(tmp);
            dbool++;
        }
    }
    return dbool;
}

bool Zoo::deleteAnimalByAge(int _age) {
    int dbool = 0;
    for(std::vector<Animal*>::iterator it = mem.begin(); it != mem.end(); it++) {
        if((*it)->getAge() == _age) {
            count[(*it)->getType()]--;
            std::vector<Animal*>::iterator tmp = it;
            it--;
            mem.erase(tmp);
            dbool++;
        }
    }
    return dbool;
}

void Zoo::print() {
    for(int i = 0; i < mem.size(); i++) {
        mem[i]->Shout();
    }
}
