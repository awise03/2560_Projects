//
// Created by Jackymora Isa and Alexander Wise on 2/20/24.
//

#include <iostream>
#include "deck.cpp"
#include "card.cpp"

using namespace std;

int main()
{
    // Create a deck
    Deck d = Deck();

    // Print the deck cards before shuffle
    cout << "\n" << "Before Shuffle: " << "\n" << d << endl;

    // Print the deck cards after shuffle
    cout << "\n" << "After Shuffle: " << "\n" << endl;
    d.shuffle();
    cout << d << endl;

    return 0 ;
}
