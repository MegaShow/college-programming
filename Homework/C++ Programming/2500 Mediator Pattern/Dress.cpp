// MegaShow
#include "Dress.hpp"

Dress::Dress(const string &name, const int price)
    : name(name), price(price) {}

Dress::Dress(const Dress &oth) 
    : name(oth.name), price(oth.price) {}

int Dress::getPrice() const {
    return price;
}

string Dress::getName() const {
    return name;
}
