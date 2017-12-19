#include "Parser.hpp"

void test() {
  Parser* parser = Parser::getInstance();
  parser->read();
  parser->parse();
  Parser::destroyInstance();
}

int main() {
  test();
  return 0;
}