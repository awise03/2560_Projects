#include <iostream>
#include <vector>

#include "mastermind.hpp"
#include "response.hpp"
#include "code.hpp"

using namespace std;

// user-based input constructor
Mastermind::Mastermind(int n, int m) : secretCode(n,m)
{}

//Default constructor with default values of code length (n) and digit range (m)
Mastermind::Mastermind() : secretCode(5,10)
{};

void Mastermind::PrintSecret()
{
    cout<< "The secret code: " ;
    secretCode.printCode();
}

Code Mastermind::humanGuess() const
{
    cout << "\nEnter your guess code: ";

    vector<int> guessCode;
    int elements;

    for(int i = 0; i < secretCode.getSize(); i++)
    {
        cin >> elements;
        guessCode.push_back(elements);
    }
    return Code(guessCode);
}

response Mastermind::getResponse(const Code &guess) const
{
    int correctPos = secretCode.checkCorrect(guess);
    int incorrectPos = secretCode.checkIncorrect(guess);

    return response(correctPos, incorrectPos);
}

bool Mastermind::isSolved(const response &correctResponse)
{
    return correctResponse.getCorrectVal() == secretCode.getSize();
}

void Mastermind::playGame()
{
    secretCode.randomInitial();

    secretCode.printCode();

    for(int a = 0; a < 10; a++)
    {
        Code guess = humanGuess();   
        response resp = getResponse(guess);
        // int correctResponse = getResponse(guess);
        cout << resp << endl;
        if(isSolved(resp))
        {
            cout << "Congrats! You guessed the code.\n";
            return;
        }
    }

    cout << "Sorry did not guess right.\n";
    secretCode.printCode();
}





