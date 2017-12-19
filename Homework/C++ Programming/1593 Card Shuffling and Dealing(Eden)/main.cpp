#include <iostream>
#include <iomanip>
#include "deck-of-cards.hpp"

void RunAllTests() {
  int count;
  std::cin >> count;

  DeckOfCards myDeckOfCards;
  for (int i = 0; myDeckOfCards.moreCards() && i < count; ++i) {
    std::cout << std::left << std::setw(19)
      << myDeckOfCards.dealCard().toString();
    if (i % 4 == 3)
      std::cout << std::endl;
  }
}

int main() {
  RunAllTests();
  return 0;
}
