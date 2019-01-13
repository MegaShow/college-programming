#include <fstream>

#include "File.h"

bool File::Write(const string& path, const string& text) {
    ofstream fout(path, ios::out);
    if (fout.fail()) {
        return false;
    }
    fout << text;
    fout.close();
    return true;
}

string File::Read(const string& path) {
    ifstream fin(path.c_str(), ios::in);
    if (fin.fail()) {
        return string();
    }
    string str;
    while (!fin.eof()) {
        char tmp[256];
        fin.getline(tmp, 255);
        str = str + tmp + '\n';
    }
    fin.close();
    return str;
}
