// MegaShow
#include "String.h"

char String::_error_sign = 0;

String::String(){
    _length = 0;
    _size = 1;
    _buff = new char[_size];
    _buff[0] = 0;
}

String::String(const char *src){
    _length = 0;
    _size = 1;
    _buff = new char[_size];
    _buff[0] = 0;
    assign(src);    
}

String::String(const String &src){
    _length = 0;
    _size = 1;
    _buff = new char[_size];
    _buff[0] = 0;
    *this = src;
}

// destructor
String::~String(){
    delete [] _buff;
}

// member methods
void String::assign(const char *src){
    delete [] _buff;
    _length = 0;
    for(int i = 0; src[i]; i++)
        _length++;
    _size = _length + 1;
    _buff = new char[_size];
    for(int i = 0; i < _length; i++)
        _buff[i] = src[i];
    _buff[_length] = 0;
}

void String::append(const char &other){
    _size++;
    char* _new_buff = new char[_size];
    for(int i = 0; i < _length; i++)
        _new_buff[i] = _buff[i];
    _length++;
    _new_buff[_size-2] = other;
    _new_buff[_size-1] = 0;
    delete [] _buff;
    _buff = _new_buff;
}

void String::clear(){
    delete [] _buff;
    _length = 0;
    _size = 1;
    _buff = new char[_size];
    _buff[0] = 0;
}

int String::compare(const String &other) const{
    for(int i = 0; i < _size || i < other._size; i++){
        if(_buff[i] < other._buff[i])
            return -1;
        else if(_buff[i] > other._buff[i])
            return 1;
    }
    return 0;
}

const char*String:: c_str() const{
    return _buff;
}

bool String::empty() const{
    return _length == 0;
}

int String::find(const String &other, int pos) const{
    for(int i = pos; i <= _length - other._length; i++){
        bool flag = true;
        for(int k = i; k < _length && k-i < other._length; k++){
            if(_buff[k] != other._buff[k-i]){
                flag = false;
                break;
            }
        }
        if(flag)
            return i;
    }
    return _length;
}

int String::length() const{
    return _length;
}

String String::substr(const int &pos, const int &count) const{
    String tmp;
    for(int i = 0; i < count; i++)
        tmp.append(_buff[pos+i]);
    return tmp;
}

// overload operators
char& String::operator[](const int &index){
    if(index >= 0 && index <= _length)
        return _buff[index];
    else
        return _error_sign;
}

void String::operator=(const String &other){
    delete [] _buff;
    _size = other._size;
    _length = other._length;
    _buff = new char[_size];
    for(int i = 0; i < _size; i++)
        _buff[i] = other._buff[i];
}

void String::operator=(const char *src){
    assign(src);
}

String String::operator+(const String &other) const{
    String tmp;
    delete [] tmp._buff;
    tmp._length = _length + other._length;
    tmp._size = tmp._length + 1;
    tmp._buff = new char[tmp._size];
    for(int i = 0; i < _length; i++)
        tmp._buff[i] = _buff[i];
    for(int i = _length; i < tmp._length; i++)
        tmp._buff[i] = other._buff[i-_length];
    tmp._buff[tmp._length] = 0;
    return tmp;
}

bool String::operator<(const String &other) const{
    return compare(other) < 0;
}

bool String::operator<=(const String &other) const{
    return compare(other) <= 0;
}

bool String::operator>(const String &other) const{
    return compare(other) > 0;
}

bool String::operator>=(const String &other) const{
    return compare(other) >= 0;
}

bool String::operator==(const String &other) const{
    return compare(other) == 0;
}

bool String::operator!=(const String &other) const{
    return compare(other) != 0;
}

// friend methods
std::ostream& operator<<(std::ostream& out, const String &str){
    out << str._buff;
    return out;
}