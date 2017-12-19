#include"header.h"
int main() {
    gameobject* g;  // gameobject是一个抽象类
    worker* w;  // worker zealot tower是派生类
    zealot* z;
    tower* t;
    double x, y;  // (x, y)表示坐标
    cin >> x >> y;
    w = new worker(x, y);
    cin >> x >> y;
    z = new zealot(x, y);
    cin >> x >> y;
    t = new tower(x, y);
    // test for select
    cout << "test for select:\n";

    g = w;
    g->select();
    g = z;
    g->select();
    g = t;
    g->select();
    // test for move
    cout << "\ntest for move:\n";

    g = w;
    g->move();
    g = z;
    g->move();
    g = t;
    g->move();
    // test for others
    cout << "\ntest for attack:\n";
    z->attack(t);
    t->attack(z);
    cout << "Zealot's hp is " << z->get_hp() << endl;
    cout << "Tower's hp is " << t->get_hp() << endl;
    cout << "\ntest for repair:\n";
    w->repair(z);  // worker将zealot的HP修复至10
    cout << "Zealot's hp is " << z->get_hp() << endl;
    int h;
    cin >> h;
    cout << "\ntest for build:\n";
    w->build(h);
    delete w;
    delete z;
    delete t;
    return 0;
}
