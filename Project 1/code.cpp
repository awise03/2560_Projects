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
    vector<int> guess;
    guess = code.secretCode;
    for(int i = 0; i < n; i++) {
        if(guess.at(i) == secretCode.at(i)){
            count++;
        }
    }
    
    return count;
}

int Code::checkIncorrect(const Code &code) {
    int count = 0;
    vector<int> guess = code.secretCode;
    vector<int> codeCopy = secretCode;
    
    for(int j = 0; j < codeCopy.size(); j++){
        for(int k = 0; k < guess.size(); k++){
            if(secretCode.at(j) == guess.at(k)){
                count++;
                
                codeCopy.erase(codeCopy.begin()+k);
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