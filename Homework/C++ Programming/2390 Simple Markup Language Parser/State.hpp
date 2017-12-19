#ifndef STATE_HPP_
#define STATE_HPP_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <string>
#include "Bulider.hpp"
using std::string;

class Parser;

class State {
public:
  virtual ~State() {}
 // handle the parser's requests and change to next state if nessesary
  virtual void handleOneChar(Parser* parser, char ch) = 0;

protected:
  string _cache;
 // transfer cache string to a token and emit it to the bulider
 virtual void emit(Bulider* dest) = 0;
};


class DataState : public State {
public:
 static State* getInstance();
 static void destroyInstance();

 virtual void handleOneChar(Parser* parser, char ch);

private:
 static State* _instance;

  virtual void emit(Bulider* dest);

 DataState() {}
 virtual ~DataState() {}
 DISALLOW_COPY_AND_ASSIGN(DataState);
};


class TagNameState : public State {
public:
 static State* getInstance();
 static void destroyInstance();

 virtual void handleOneChar(Parser* parser, char ch);

private:
 static State* _instance;

  virtual void emit(Bulider* dest);

 TagNameState() {}
 virtual ~TagNameState() {}
 DISALLOW_COPY_AND_ASSIGN(TagNameState);
};

#endif
