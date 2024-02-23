#include "card.h"
#include <iostream>

Card::Card() {
    value = 0;
    suit = "";
}

void Card::setValue(int val) {
    value = val;
}

void Card::setSuit(string s) {
    suit = s;
}

int Card::getValue() { 
    return value;
}

string Card::getSuit() {
    return suit;
}

ostream & operator<<(ostream&out, const Card &c1) {
    out << "Suit: " << c1.suit << " \nCard Value: " << c1.value << endl;
    return out;
}

Card& Card::operator=(const Card &c1) {
    if(this != &c1) { 
        value = c1.value;
        suit = c1.suit;
    }
    return *this;
}