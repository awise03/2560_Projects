/*
    * main.cpp
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/

#include <iostream>
#include <vector>

#include "code.cpp"
#include "mastermind.cpp"
#include "response.cpp"

using namespace std;

int main(){
    /**********************************/
    /*             Part B             */           
    /**********************************/

    bool customize;
    Mastermind game;

    cout << "Would you like to customize your code length and range of digits\n\
    press 0 for No and 1 for Yes ";
    cin >> customize;
    if (customize)
    {
        int n, m;

        cout << "Enter The code length (n)" << endl;
        cin >> n;

        cout << "Enter the range of digits (m)" << endl;
        cin >> m;

        game = Mastermind(n, m);
    }


    game.playGame();// Play the game

    return 0;
}
