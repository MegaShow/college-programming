#ifndef BULIDER_HPP_
#define BULIDER_HPP_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <vector>
#include <stack>
#include "Token.hpp"

class Bulider {
public:
 static Bulider* getInstance();
 static void destroyInstance();

  // check the token's validity in current nesting structure
  // if valid, record it in _tokens, if not, set _error true
  void handleOneToken(Token token);
  void display();

private:
  static Bulider* _instance;

  std::vector<Token> _tokens;
  std::stack<Token> _stack;
  bool _error;

  Bulider() { _error = false; }
  ~Bulider() {}
  DISALLOW_COPY_AND_ASSIGN(Bulider);
};

#endif