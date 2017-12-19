// MegaShow
#include <string>
#include "card.hpp"

const char* Card::faceNames[Card::totalFaces] = {"Ace", "Deuce", "Three", "Four", "Five", 
        "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

const char* Card::suitNames[Card::totalSuits] = {"Hearts", "Diamonds", "Clubs", "Spades"};

Card::Card(int cardFace, int cardSuit){
    face = cardFace;
    suit = cardSuit;
}

std::string Card::toString() const{
    return std::string(faceNames[face]) + " of " + std::string(suitNames[suit]);
}

int Card::getFace() const{
    return face;
}

int Card::getSuit() const{
    return suit;
}