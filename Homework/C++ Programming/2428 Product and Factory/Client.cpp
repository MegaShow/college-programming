#include <iostream>
#include "Product.hpp"
#include "Factory.hpp"
using std::cin;

void test() {
  Factory* factory = NULL;
  int choose;
  cin >> choose;

  switch (choose) {
    case 0:
      factory = new AppleFactory();
      break;
    case 1:
    default:
      factory = new XiaomiFactory();
      break;
  }

  Laptop* laptop = factory->produceLaptop();
  MobilePhone* phone = factory->produceMobilePhone();

  laptop->compileCppProgram();
  phone->sendShortMessage();

  delete laptop;
  delete phone;

  delete factory;
}

int main() {
  test();
  return 0;
}
