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
Deck::Deck() : firstCard(nullptr), head(nullptr)
{
    for(int suit = 0; suit < 4; suit++)
    {
        for(int value = 1; value <=13; value++)
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

Deck::~Deck() { 
    // Starts at the front of the deck
    head = firstCard;
    // Moves forward until we reach the end of the deck
    while(head != nullptr) {
        DeckNode<Card> *temp = head;
        head = head->next;
        // Deletes the node at the current deck location. 
        delete temp;
    }
}

// Takes the inputted card and places it in the back of the deck.
void Deck::replace(const Card &c1){
    DeckNode<Card>* temp = new DeckNode<Card>(c1);

    // Sets the head of the deck to the current card if it is at the end of the deck
    if(head == nullptr) {
        head = temp;
    } else {
        // Creates a temporary variable equal to the loaction of head
        DeckNode<Card>* current = head;
        // Iterates through each item in the deck until we reach the end of the list, places the card in the back of the list.
        while(current -> next != nullptr) {
            current = current -> next;
        }

        current -> next = temp;
    }
    
}

Card Deck::deal()
{
    if(firstCard == nullptr)
    {
        // Handle case when deck is empty
        cerr << "Error: Deck is empty. Unable to deal a card." << endl;
        // Return a default-constructed card or throw an exception
        // depending on your error handling strategy
        return Card();// This returns a default-constructed card
    }
    else
    {   //Get the top card
        Card topCard = firstCard->dataValue;
        // Remove the top card from the deck
        DeckNode<Card> *temp = firstCard;
        firstCard = firstCard->next;
        delete temp;
        // Return the top card
        return topCard;

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

Card Deck::deal()
{
    if(firstCard == nullptr)
    {
        // Handle case when deck is empty
        cerr << "Error: Deck is empty. Unable to deal a card." << endl;
        // Return a default-constructed card or throw an exception
        // depending on your error handling strategy
        return Card();// This returns a default-constructed card
    }
    else
    {   //Get the top card
        Card topCard = firstCard->dataValue;
        // Remove the top card from the deck
        DeckNode<Card> *temp = firstCard;
        firstCard = firstCard->next;
        delete temp;
        // Return the top card
        return topCard;

    }
}


