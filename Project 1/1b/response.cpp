#include <iostream>
#include "response.hpp"

response::response(int c, int i){
    correctVal = c;
    incorrectPos = i;
}

int response::getCorrectVal() const {
    return correctVal;
}

int response::getIncorrectPos() const {
    return incorrectPos;
}

void response::setCorrectVal(int c){
    correctVal = c;
}

void response::setIncorrectPos(int i){
    incorrectPos = i;
}

bool operator==(const response& r1, const response& r2){
    return (r1.correctVal == r2.correctVal) && (r1.incorrectPos == r2.incorrectPos);
}

ostream & operator<<(ostream&out, const response& r1){
    out << "Correct Position: " << r1.correctVal << " \nIncorrect Position: " << r1.incorrectPos;
    return out;
}