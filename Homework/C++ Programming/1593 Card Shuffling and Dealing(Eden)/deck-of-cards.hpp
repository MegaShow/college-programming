#ifndef DECK_OF_CARDS_HPP_
#define DECK_OF_CARDS_HPP_
#include <vector>
#include "card.hpp"

class DeckOfCards {
  public:
    DeckOfCards();
    Card dealCard();
    bool moreCards() const;
  private:
    std::vector<Card> deck;
    int currentCard;
};
#endif
