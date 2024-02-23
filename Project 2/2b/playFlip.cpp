//
// Created by Jackymora Isa and Alexander Wise on 2/22/24.
//
#include <iostream>
#include "playFlip.h"
#include "deck.h"

using namespace std;

void playFlip()
{
    int score = 0;
    // Print out game instructions
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

    // Initialize a new deck and shuffle 3 times
    Deck d = Deck();
    d.shuffle();
    d.shuffle();
    d.shuffle();

    //Deck copy = d;
    //prints top 24 cards
    cout << "Top 24 cards in the deck:" << endl;
    for(int i =0; i <24; i++)
    {
        Card c1 = d.deal();
        cout << (i+1) <<". " << c1 << endl;
    }


    cout << endl;
    int cards = 24;
    string move = "";
    // Loops until the player decides to end their move or the deck is empty.
    while(move != "stand" || cards != 0) {
        cout << "\nYour current score is " << score;
        cout << "\nYou have " << cards << " cards remaining.";
        cout << "\nWould you like to flip your card or stand (flip, stand)? " << endl;
    
        cin >> move;

        if(move == "flip") {
            // Pulls a card from the top of the deck
            Card card = d.deal();
            cout << "\n Your card is: \n " << card << endl;
            // Compares card value to determine the score to be added
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
            cards--;
        // Breaks out if the player decides to stand
        } else if (move == "stand"){
            break;
        } else {
            "Incorrect input, please try again";
        }
        
    }

    cout << "\nYour final score is: " << score << endl;
    cout << "\nRemaining cards: \n" << d << endl;
}