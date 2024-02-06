#include <iostream>
#include <vector>

#include "mastermind.hpp"
#include "response.hpp"
#include "code.hpp"

using namespace std;
//Mastermind Class Implementation

// user-based input constructor
Mastermind::Mastermind(int n, int m) : secretCode(n, m)
{};

// Default constructor with default values of code length (n) and digit range (m)
Mastermind::Mastermind() : secretCode(5, 10)
{};

// Function to print the Secret Code
void Mastermind::PrintSecret()
{
    cout<< "The secret code: " ;
    secretCode.printCode();
}

// Function to print the guess from the user
Code Mastermind::humanGuess() const {
    cout << "\nEnter your guess code:\n";

    vector<int> guessCode; // initializes guess vector
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

// Function that get response for a guess
response Mastermind::getResponse(const Code &guess) const
{
    int correctPos = secretCode.checkCorrect(guess); // checks if value is in correct position
    int incorrectPos = secretCode.checkIncorrect(guess); // checks if value is in incorrect position

    return response(correctPos, incorrectPos);
}

// Function to check if the correct response indicates the code is solved
bool Mastermind::isSolved(const response &correctResponse)
{
    return correctResponse.getCorrectVal() == secretCode.getSize();
}

// Function to play Mastermind game
void Mastermind::playGame()
{
    secretCode.randomInitial();// Generates a random secret code

    secretCode.printCode();// Displays the secret code

    for(int a = 0; a < 10; a++)
    {
        Code guess = humanGuess();// Get a guess from user
        response resp = getResponse(guess);// Get a response for user
        cout << resp << endl; // Display the response
        if(isSolved(resp))
        {
            cout << "Congrats! You guessed the code.\n";
            return;
        }
    }

    cout << "You failed! Womp, Womp.\n";
    secretCode.printCode(); // Print the secret code if player fails
}





