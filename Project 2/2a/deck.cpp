//
// Created by Jackymora Isa and Alexander Wise on 2/20/24.
//

#include <iostream>
#include <vector>
#include "deck.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// constructor : creates deck of cards in order
Deck::Deck() : firstCard(nullptr)
{
    for(int suit = 0; suit < 4; suit++)
    {
        for(int value =1; value <=13; value++)
        {
            Card newCard = Card();
            newCard.setValue(value);
            switch (suit)
            {
                case 0:
                    newCard.setSuit("Club");
                    break;
                case 1:
                    newCard.setSuit("Diamond");
                    break;
                case 2:
                    newCard.setSuit("Spade");
                    break;
                case 3:
                    newCard.setSuit("Heart");
                    break;
            }
            addCardToDeck(newCard);
        }
    }
}

//  prints card in deck
ostream& operator << (ostream& out, Deck& deck)
{
    DeckNode<Card>* current = deck.firstCard;
    while(current)
    {
        out << current->dataValue << "\n";
        current = current->next;
    }
    return out;
}

// function that add cards in the end of the deck
void Deck::addCardToDeck(const Card &c1)
{
    DeckNode<Card>* newNode= new DeckNode<Card>(c1);

    if(!firstCard)
    {
        firstCard = newNode;
    }
    else
    {
        DeckNode<Card>* current = firstCard;
        while(current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Deck::shuffle()
{
    // Converts linked list to vector
    vector <Card> cards;
    DeckNode<Card> *current = firstCard;
    while (current) {
        cards.push_back(current->dataValue);
        current = current->next;
    }

    // shuffle vector of cards using
    srand(time(0)); // randomness seed
    for (int i = cards.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(cards[i], cards[j]);
    }
    // Update linked list with shuffled cards
    current = firstCard;
    for(const Card& card : cards)
    {
        current->dataValue = card;
        current = current->next;
    }
}


