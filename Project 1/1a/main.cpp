#include <iostream>
#include <vector>

#include "code.cpp"


using namespace std;

int main(){
    /**********************************/
    /*             Part A             */           
    /**********************************/
    vector<int> testCase = {6, 2, 5, 8, 2};
    Code primaryTest(testCase);
    primaryTest.randomInitial();

    cout << "Secret code: ";
    primaryTest.printCode();

    vector<int> case1 = {1, 2, 3, 4, 5};
    vector<int> case2 = {2, 1, 2, 2, 2};
    vector<int> case3 = {1, 3, 3, 4, 5};

    Code Guess1(case1);
    Code Guess2(case2);
    Code Guess3(case3);

    cout << "\n\nGuess 1: "; 
    Guess1.printCode();
    cout << "\nGuess 1 checkCorrect(): " << primaryTest.checkCorrect(Guess1) << endl;
    cout << "Guess 1 checkIncorrect(): " << primaryTest.checkIncorrect(Guess1) << endl;

    cout << "\nGuess 2: "; 
    Guess2.printCode();
    cout << "\nGuess 2 checkCorrect(): " << primaryTest.checkCorrect(Guess2) << endl;
    cout << "Guess 2 checkIncorrect(): " << primaryTest.checkIncorrect(Guess2) << endl;

    cout << "\nGuess 3: "; 
    Guess3.printCode();
    cout << "\nGuess 3 checkCorrect(): " << primaryTest.checkCorrect(Guess3) << endl;
    cout << "Guess 3 checkIncorrect(): " << primaryTest.checkIncorrect(Guess3) << endl;

    return 0;
}

