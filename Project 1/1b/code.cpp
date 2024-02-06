#include "code.hpp"
#include <random>
#include <iostream>

using namespace std;

// Creates a vector of length n and fills it with elements randomly.
Code::Code(int length, int range) {
    n = length;
    m = range;
    secretCode.reserve(n);
}

// Constructs a code object using the provided vector.
Code::Code(vector<int> &guess){
    secretCode = guess;
}

// Randomly generates a code of length n and in range of 0 to m-1
void Code::randomInitial() {
    srand(time(0));
    int randVal;

    // Loops through all indices in the array
    for(int i = 0; i < n; i++) {
        // Generates a random value between 0 and m-1
        randVal = rand() % (m);
        // Places that new value in the back of the vector.
        secretCode.push_back(randVal);
    }
}

// Function to check for the correct position and value
int Code::checkCorrect(const Code &c1) const {
    int count = 0;
    // Loops through each element in the secretCode vector
    for(int i = 0; i < secretCode.size(); i++) {
        // Increments by one if the two values are the same
        if(c1.secretCode.at(i) == secretCode.at(i)){
            count++;
        }
    }
    // Returns the count
    return count;
}

// Function to check for the correct value and incorrect position
int Code::checkIncorrect(const Code &c1) const {
    int count = 0;
    vector<bool> used(secretCode.size(), false);
    // Loops through each value in secretCode
    for(int codeItr = 0; codeItr < secretCode.size(); codeItr++) {

        // Loops through each value in the passed code
        for(int guessItr = 0; guessItr < c1.secretCode.size(); guessItr++) {
            
            // Marks values of the correct position as used to be ignored later on
            if(secretCode.at(codeItr) == c1.secretCode.at(codeItr)) {
                used.at(codeItr) = true;
                break;
            }

            // Checks to see if the code being checked has been used yet and if the values are the same
            if(!used.at(guessItr) && secretCode.at(codeItr) == c1.secretCode.at(guessItr) && guessItr != codeItr){
                // Makes it so this value can't be checked again
                used.at(guessItr) = true;
                // Increments count 
                count++;
                // Exits inner loop so no other values are checked
                break;
            }
        }
    }
    // Returns the count
    return count;
}

// Returns the length of the code
int Code::getSize() const {
    return n;
}

// Returns the range of digits allowed in the code
int Code::getRange() const {
    return m;
}

// Returns the secretCode vector
vector<int> Code::getCode(){
    return secretCode;
}
// Prints the secretCode vector
void Code::printCode(){
    for(int i = 0; i < secretCode.size(); i++){
        cout << secretCode.at(i) << " ";
    }
}