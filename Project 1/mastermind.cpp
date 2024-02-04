#include <iostream>
#include "mastermind.hpp"
#include <vector>

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

    for(int i = 0; i < secretCode.length(); i++)
    {
        cin>> elements;
        guessCode.push_back(elements);
    }
    return Code(guessCode);
}

response Mastermind::getResponse(const Code &guess) const
{
    
}




