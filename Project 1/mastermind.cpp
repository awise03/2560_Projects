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


Code Mastermind::humanGuess()
{
    cout << "Enter your guess code: ";

    vector<int> guessCode;
    int elements;

    for(int i = 0; i < secretCode.getSecretCodeSize(); i++)
    {
        cin>> elements;
        guessCode.push_back(elements);
    }
    return Code(guessCode);
}

response Mastermind::getResponse(const Code g1)
{
    int correct = secretCode.checkCorrect(g1);
    int incorrect = secretCode.checkIncorrect(g1);
    response res = response(correct, incorrect);

    // cout << "Response: " << res << endl;

    return res;
}

bool Mastermind::isSolved(response r1)
{
    return r1.getCorrectVal() == secretCode.getSecretCodeSize();
}

void Mastermind::playGame()
{
    secretCode.randomInitial();

    secretCode.printCode();
    int remainingGuesses = 9;
    bool solved = false;

    while (!solved && remainingGuesses >= 0)
    {
        Code guess = humanGuess();   
        response correctResponse = getResponse(guess);
        
        solved = isSolved(correctResponse);
        remainingGuesses--;
    }
    
    if(solved)
    {
        cout<<"Congratulation!! You solved it!!" <<endl;
    }
    else
    {
        cout << "You're a Failure, You can never make it.\n";
        secretCode.printCode();
    }
    
}





