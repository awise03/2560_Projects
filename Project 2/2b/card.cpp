#include "card.h"
#include <iostream>

// Card Constructor. Initializes to temporary values
Card::Card() {
    value = 0;
    suit = "";
}

// Sets values of the card
void Card::setValue(int val) {
    value = val;
}


// Sets suit of the card
void Card::setSuit(string s) {
    suit = s;
}

// Returns the value of the card
int Card::getValue() { 
    return value;
}


// Returns the suit of the card
string Card::getSuit() {
    return suit;
}

// Overriding ostream operator to print the suit and value
ostream & operator<<(ostream&out, const Card &c1) {
    out << "Suit: " << c1.suit << " \nCard Value: " << c1.value << endl;
    return out;
}

// Copy Constructor.
Card& Card::operator=(const Card &c1) {
    if(this != &c1) { 
        value = c1.value;
        suit = c1.suit;
    }
    return *this;
}