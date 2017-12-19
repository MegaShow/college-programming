#include <iostream>
using namespace std;

class SingleDog {
public:
    //constructor
    SingleDog(int id_, char* name_);

    //copy constructor
    SingleDog(const SingleDog &other);

    //desctructor
    ~SingleDog();

    //return the count of single dog
    static int getCount();

    //print some infomation
    void print() const {
        cout << "SingleDog " << id << ". My name is " << name << endl;
    }

private:
    const int id; 
    char *name; 
    static int count; // the count of single dog
};