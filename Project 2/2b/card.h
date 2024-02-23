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
        Card& operator =(const Card& other);
        void setValue(int);
        void setSuit(string);
        int getValue();
        string getSuit();

        friend ostream & operator<<(ostream &out, const Card &c1);

};


#endif 