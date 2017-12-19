#ifndef _DRESS_
#define _DRESS_
#include <iostream>
using std::string;
class Dress {
    private:
        string name;
        int price;
    public:
        Dress(const string & name, const int price);
        Dress(const Dress & oth);
        int getPrice() const;
        string getName() const;
};

#endif