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

    cout << "Would you like to customize your Lockbox length and range of digits\n\
    press 0 for No and 1 for yes ";
    cin >> customize;
    if (customize){
        int n , m;

        cout << "Enter The code length (n)" <<endl;
        cin >> n;

        cout << "Enter the range of digits" << endl;
        cin >> m;

        Mastermind game = Mastermind(n,m);
    }


    game.playGame();

    return 0;
}
