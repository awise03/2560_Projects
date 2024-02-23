//
// Created by Jackymora Isa and Alexander Wise on 2/20/24.
//

#include <iostream>

#ifndef CARD_H
#define CARD_H

using namespace std;

class Card {
    private:
        int value;
        string suit;
    public:
        Card();
        void setValue(int);
        void setSuit(string);
        int getValue();
        string getSuit();

        Card& operator = (const Card& c1);

        friend ostream & operator<<(ostream &out, const Card &c1);

};


#endif 