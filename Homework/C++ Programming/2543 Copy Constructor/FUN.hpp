#ifndef FUN_HPP
#define FUN_HPP
class FUN
{
private:

    char *str;
public:
    FUN(char *s);

    FUN(const FUN& C);

    ~FUN()
    {
        delete[]str;
    }
    void show();
};

#endif