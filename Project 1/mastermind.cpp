#include <iostream>
#include "mastermind.hpp"
#include <vector>
#include "response.hpp"
#include "code.hpp"

using namespace std;

// user-based input constructor
Mastermind::Mastermind(int n, int m):secretCode(n,m)
{
    cout << "Enter The code length (n)" <<endl;
    cin >> n;

    cout << "Enter the range of digits" << endl;
    cin >>m;
}

//Default constructor with default values of code length (n) and digit range (m)
Mastermind::Mastermind():secretCode(5,10)
{};

void Mastermind::PrintSecret()
{
    cout<< "The secret code: " ;
    secretCode.printCode();
}

Code Mastermind::humanGuess() const
{
    cout << "Enter your guess code: ";

    vector<int> guessCode;
    int elements;

    for(int i = 0; i < secretCode.size(); i++)
    {
        cin>> elements;
        guessCode.push_back(elements);
    }
    return Code(guessCode);
}

int  Mastermind::getResponse(const Code &guess) const
{
    int correctResponse = secretCode.checkCorrect(guess);

    cout << "Response: " << correctResponse << endl;

    return correctResponse;
}

bool Mastermind::isSolved(int correctReponse) const
{
    return correctResponse == secretCode.getlength();
}

void Mastermind::playGame()
{
    secretCode.randomInitial();

    secretCode.printCode();

    for(int a=1; a <= k; a++)
    {
        Code guess = humanGuess();   

        int correctResponse = getResponse(guess);

        if(isSolved(correctResponse))
        {
            cout << "Congrats! You guessed the code.\n";
            return;
        }
    }

    cout << "Sorry did not guess right.\n";
    secretCode.printCode();
}





