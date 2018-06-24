#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Compiler final {
  public:
    Compiler(string input, function<void(const int, const string&)> print = nullptr);
    int Compile();
    string GetOutput(bool isCompileToBinary = false);

  private:
    static int ParseInteger(stringstream& ss, char delim, int bits,
        bool isUnsigned = false, bool isHex = false);
    static int ParseRegister(stringstream& ss, char delim);

    static set<string> R;
    static set<string> I;
    static set<string> J;
    static map<string, int> OpCode;

    vector<string> input;
    vector<int> output;
    string err;
    function<void(const int, const string&)> print;
};

#endif // __COMPILER_H__
