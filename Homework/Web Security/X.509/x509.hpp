#ifndef __X509_HPP__
#define __X509_HPP__

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

struct Value {
    uint8_t type;
    std::vector<uint8_t> val;
    std::string str;
};

class X509 {
public:
    X509(std::string filename);
    size_t size();
    std::string getBase64String(size_t i);
    void parse(size_t i = 0);
    void print();

private:
    static std::vector<uint8_t> decodeBase64(std::string base64);
    static void parseDer(std::vector<uint8_t> v);

    std::vector<std::string> raw;
    static std::vector<std::string> parseKey;
    static std::vector<Value> parseValue;

    static const std::string BASE64_TABLE;
    static const std::string CERT_BEGIN;
    static const std::string CERT_END;
    static const std::map<std::string, std::string> OBJECT_ID;
};

#endif // __X509_HPP__
