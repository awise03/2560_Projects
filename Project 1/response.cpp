#include <iostream>
#include "response.hpp"

response::response(int c, int i){
    correctVal = c;
    incorrectPos = i;
}

int response::getCorrectVal(){
    return correctVal;
}

int response::getIncorrectPos(){
    return incorrectPos;
}

void response::setCorrectVal(int c){
    correctVal = c;
}

void response::setIncorrectPos(int i){
    incorrectPos = i;
}

bool response::operator==(const response& r1){
    return correctVal == r1.correctVal && incorrectPos == r1.incorrectPos;
}

ostream & operator<<(ostream&out, const response& r1){
    out << r1.correctVal << " " << r1.incorrectPos;
    return out;
}