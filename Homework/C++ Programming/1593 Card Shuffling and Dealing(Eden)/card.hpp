#ifndef CARD_HPP_
#define CARD_HPP_
#include <string>

class Card {
  public:
    static const int totalFaces = 13;
    static const int totalSuits = 4;

    Card(int cardFace, int cardSuit);
    std::string toString() const;

    int getFace() const;
    int getSuit() const;
    
  private:
    int face;
    int suit;
    static const char* faceNames[totalFaces];
    static const char* suitNames[totalSuits];
};
#endif
