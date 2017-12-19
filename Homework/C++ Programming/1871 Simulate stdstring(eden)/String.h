#ifndef SSCPP2014_STRING_H
#define SSCPP2014_STRING_H
 
#include <iostream>
 
class String {
  private:
    char *_buff;
    int _length, _size;  // _size is of the allocated memory
 
  public:
    // constructors
    String();
    explicit String(const char *src);
    String(const String &src);
    // destructor
    ~String();
    // member methods
    void assign(const char *src);
    void append(const char &other);
    void clear();
    int compare(const String &other) const;
    const char* c_str() const;
    bool empty() const;
    int find(const String &other, int pos = 0) const;
    int length() const;
    String substr(const int &pos, const int &count) const;
    // overload operators
    char& operator[](const int &index);
    void operator=(const String &other);
    void operator=(const char *src);
    String operator+(const String &other) const;
    bool operator<(const String &other) const;
    bool operator<=(const String &other) const;
    bool operator>(const String &other) const;
    bool operator>=(const String &other) const;
    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    // friend methods
    friend std::ostream& operator<<(std::ostream& out, const String &str);
    // non-meaning static property
    static char _error_sign;  // initial as any char is okay
};
 
#endif
