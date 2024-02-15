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

