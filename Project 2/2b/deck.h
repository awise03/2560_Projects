#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "deckNode.h"
#include <iostream>

class Deck {
    public:
        // Constructor to create deck with all the cards in order
        Deck();
        // Function to shuffle cards in deck
        void shuffle();
        // Overloaded << operator to print the cards in the deck
        friend ostream& operator << (ostream &out, Deck &d1);

        void replace(const Card &c1);

        Card deal();

        ~Deck();
    private:
        // Pointer to the first card on the deck
        DeckNode<Card>* firstCard;

        DeckNode<Card>* head;
        // Function to create node for card and add it to the end of the deck
        void addCardToDeck(const Card& c1);

    
};

#endif