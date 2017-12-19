#ifndef TOKEN_HPP_
#define TOKEN_HPP_
#include <string>
using std::string;

struct Token {
  // DATA, OPEN_TAG, CLOSE_TAG
  string type;
  string content;
  // nesting depth
  int depth;
};

#endif
