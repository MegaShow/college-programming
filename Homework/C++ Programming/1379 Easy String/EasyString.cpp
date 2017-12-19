// MegaShow
// [04] Easy String
#include <string>
#include "EasyString.hpp"
using std::string;

void Assign(char * & str, int & len){
  str = new char[len+1];
}

void AddTwo(string & a, char * & b, char * & c){
  a += b;
  a += c;
  delete [] b;
  delete [] c;
}
