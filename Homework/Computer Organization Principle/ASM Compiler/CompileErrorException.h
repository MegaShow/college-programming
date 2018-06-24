#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>

using namespace std;

class CompileErrorException final : public exception {
  public:
    CompileErrorException(string err) : err("Compile Error:\n" + err) {}

    virtual const char* what() const noexcept override {
        return err.c_str();
    }

  private:
    string err;
};

#endif // __EXCEPTION_H__
