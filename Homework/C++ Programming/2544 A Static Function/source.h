// MegaShow
#ifndef SOURCE_H_
#define SOURCE_H_


class Exp {
private:
    static int count;
public:
    static int get_Exp() {
        return count;
    }
    Exp() {
        count++;
    }
    ~Exp() {
        count--;
    }
};

int Exp::count = 0;

#endif