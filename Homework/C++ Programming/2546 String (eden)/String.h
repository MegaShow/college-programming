// MegaShow
#ifndef STRING_H_
#define STRING_H_

#include <iostream>
#include <cstring>

class String {
private:
    char* str;
public:
    String(const char* s) {
        int len = strlen(s);
        str = new char[len+1];
        for(int i = 0; i <= len; i++)
            str[i] = s[i];
    }

    String(const String& s) {
        int len = strlen(s.str);
        str = new char[len+1];
        for(int i = 0; i <= len; i++)
            str[i] = s.str[i];
    }

    ~String() {
        delete [] str;
    }

    String operator=(const String& s) {
        if(this == &s)
            return *this;
        delete [] str;
        int len = strlen(s.str);
        str = new char[len+1];
        for(int i = 0; i <= len; i++)
            str[i] = s.str[i];
        return *this;
    }

    char& operator[](int pos) {
        return str[pos];
    }

    friend std::ostream& operator<<(std::ostream& out, const String& s);
};

std::ostream& operator<<(std::ostream& out, const String& s) {
    out << s.str;
    return out;
}

#endif
