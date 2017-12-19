// MegaShow
#include "deck-of-cards.hpp"

DeckOfCards::DeckOfCards(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            deck.push_back(Card(j, i));
        }
    }
    currentCard = 0;
}

Card DeckOfCards::dealCard(){
    if(currentCard < deck.size())
        return deck[currentCard++];
}

bool DeckOfCards::moreCards() const{
    return currentCard < deck.size();
}