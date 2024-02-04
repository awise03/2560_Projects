#include "code.hpp"
#include <random>
#include <iostream>

using namespace std;

Code::Code(int length, int range) {
    n = length;
    m = range;
    secretCode.reserve(n);
    randomInitial();
}

Code::Code(vector<int> &guess){
    secretCode = guess;
}

void Code::randomInitial() {
    srand(time(0));
    int randVal;
    for(int i = 0; i < n; i++) {
        randVal = rand() % (m);
        secretCode.push_back(randVal);
    }
}

int Code::checkCorrect(const Code &code) {
    int count = 0;
    vector<int> guess = code.secretCode;
    for(int i = 0; i < secretCode.size(); i++) {
        if(guess.at(i) == secretCode.at(i)){
            count++;
        }
    }
    
    return count;
}

int Code::checkIncorrect(const Code &c1){
    int count = 0;
    bool ignore = false;
    vector<int> codeCopy = secretCode;
    vector<bool> used(secretCode.size(), false);

    for(int j = 0; j < codeCopy.size(); j++) {

        for(int k = 0; k < c1.secretCode.size(); k++) {

            if(!used.at(k) && codeCopy.at(j) == c1.secretCode.at(k) && j != k){
                used.at(k) = true;
                count++;
                break;
            }
        }
    }
    return count;
}

vector<int> Code::getCode(){
    return secretCode;
}

void Code::printCode(){
    for(int i = 0; i < secretCode.size(); i++){
        cout << secretCode.at(i) << " ";
    }
}