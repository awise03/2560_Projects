#include <iostream>
#include "response.hpp"

// Constructor: Initializes a response object with correct value and incorrect position
response::response(int c, int i){
    correctVal = c;
    incorrectPos = i;
}

// Getter function: Returns the correct value
int response::getCorrectVal() const {
    return correctVal;
}

// Getter function: Returns the incorrect position
int response::getIncorrectPos() const {
    return incorrectPos;
}

// Setter function: Sets the correct value
void response::setCorrectVal(int c){
    correctVal = c;
}

// Setter function: Sets the incorrect position
void response::setIncorrectPos(int i){
    incorrectPos = i;
}

// Overloaded equality operator: Compares two responses for equality
bool operator==(const response& r1, const response& r2){
    return (r1.correctVal == r2.correctVal) && (r1.incorrectPos == r2.incorrectPos);
}

// Overloaded output stream operator: Prints the response details
ostream & operator<<(ostream&out, const response& r1){
    out << "Correct Position: " << r1.correctVal << " \nIncorrect Position: " << r1.incorrectPos;
    return out;
}