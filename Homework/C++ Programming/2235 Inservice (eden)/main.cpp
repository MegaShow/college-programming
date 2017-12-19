#include <iostream>
#include "inservice.h"
using namespace std;
 
int main() {
    string name, sno, wno;
    int sex;

    cin >> name;
    cin >> sex;
    cin >> sno;
    cin >> wno;

    InService is(name, sex, sno, wno);

    Person* p = &is;
    Student* s = &is;
    Worker* w = &is; 
 
    cout << p->getName() << endl;
    cout << p->getSex() << endl;
    cout << s->getName() << endl;
    cout << s->getSex() << endl;
    cout << s->getSno() << endl;
    cout << w->getName() << endl;
    cout << w->getSex() << endl;
    cout << w->getWno() << endl;
    return 0;
}