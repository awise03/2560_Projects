//
// Created by Jackymora Isa on 2/22/24.
//

#include "playFlip.h"
#include "deck.h"

using namespace std;

void playFlip()
{
    int score = 0;

    cout << "Welcome to Flip game!" << endl;
    cout << "A deck of 52 cards will be shuffled, and the top 24 cards will be available for uou to draw from." << endl;
    cout << "Either select a card to turn over by inputing a number between 1 and 24." << endl;
    cout << "To end the game type in a 0" "\n" << "If a card is turned over, you will gain or lose points depending on the card." <<endl;
    cout << "10 points for an ace \n"
         << "5 points for a king, queen or jack \n"
         << "Loses half your points for a 7 \n"
         << "Loses all your points for a 2,3,4,5 or 6 \n"
         << "Receive 1 point extra, in addition to the above, for a heart" <<endl;
    cout << "Try to end the game with as many points as possible! if you flip all 24 cards,\n "
            "the deck will be reshuffled and a new set of 24 will be drawn, and the game will continue." << endl;

    Deck d = Deck();
    d.shuffle();
    d.shuffle();
    d.shuffle();

    //cout << d << endl;
    cout << endl;
    string move = "";
    while(move != "stand") {
        cout << "\nYour current score is " << score;
        cout << "\nWould you like to flip your card or stand (flip, stand)? " << endl;
    
        cin >> move;
        if(move == "flip") {
            Card card = d.deal();
            cout << "\n Your card is: \n " << card << endl;
            if(card.getValue() == 1) {
                score += 10;
            } else if(card.getValue() >= 11 && card.getValue() <= 13){
                score += 5;
            } else if(card.getValue() == 7) {
                score /= 2;
            } else if (card.getValue() >= 2 && card.getValue() <= 6){
                score = 0;
            }
            if(card.getSuit() == "Heart") {
                score ++;
            }
        } else {
            break;
        }
    }

    cout << "\nYour final score is: " << score << endl;
}
