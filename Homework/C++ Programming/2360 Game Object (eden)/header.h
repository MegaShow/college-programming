// MegaShow
#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class gameobject {
protected:
    double x, y, hp;
public:
    gameobject(double _x, double _y) : x(_x), y(_y), hp(10) {}
    virtual void select() const = 0;
    virtual void move() = 0;
    virtual void attack(gameobject* obj) = 0;
    double get_hp() { return hp; }
    void set_hp(double _hp) { hp = _hp; }
};


class worker : public gameobject {
private:
public:
    worker(double x, double y) : gameobject(x, y) {}
    virtual void select() const { std::cout << "Scv good to go, sir!" << std::endl; }
    virtual void move() { x += 1; y += 1; std::cout << "Worker moves to (" << x << ", " << y << ")" << std::endl; }
    virtual void attack(gameobject* obj) {}
    void repair(gameobject* obj) { obj->set_hp(10); }
    void build(int h) {
        for(int i = 1; i <= h; i++) {
            for(int j = 0; j < h - i; j++)
                std::cout << ' ';
            for(int j = 0; j < i * 2 - 1; j++)
                std::cout << '*';
            std::cout << std::endl;
        }
    }
};


class zealot : public gameobject {
private:
public:
    zealot(double x, double y) : gameobject(x, y) {}
    virtual void select() const { std::cout << "My life for Aiur!" << std::endl; }
    virtual void move() { x += 2; y += 2; std::cout << "Zealot moves to (" << x << ", " << y << ")" << std::endl; }
    virtual void attack(gameobject* obj) { obj->set_hp(obj->get_hp() - 1); }
};


class tower : public gameobject {
private:
public:
    tower(double x, double y) : gameobject(x, y) {}
    virtual void select() const { std::cout << "~" << std::endl; }
    virtual void move() { std::cout << "Tower cannot move." << std::endl; }
    virtual void attack(gameobject* obj) { obj->set_hp(obj->get_hp() - 1); }
};

#endif
