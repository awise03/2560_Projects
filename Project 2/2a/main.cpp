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
