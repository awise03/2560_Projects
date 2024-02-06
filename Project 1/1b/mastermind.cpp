#include <iostream>
#include <vector>

#include "mastermind.hpp"
#include "response.hpp"
#include "code.hpp"

using namespace std;

// user-based input constructor
Mastermind::Mastermind(int n, int m) : secretCode(n, m)
{};

// Default constructor with default values of code length (n) and digit range (m)
Mastermind::Mastermind() : secretCode(5, 10)
{};


void Mastermind::PrintSecret()
{
    cout<< "The secret code: " ;
    secretCode.printCode();
}

Code Mastermind::humanGuess() const {
    cout << "\nEnter your guess code:\n";

    vector<int> guessCode;
    int element;

    for (int i = 0; i < secretCode.getSize(); i++)
    {
        cout << "Digit " << i + 1 << ": ";
        // Check if the input is a valid integer
        while (!(cin >> element)) {
            cout << "Error: Please enter a valid integer.\n";
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Digit " << i + 1 << ": ";
        }

        guessCode.push_back(element);
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

    cout << "You failed! Womp, Womp.\n";
    secretCode.printCode();
}





