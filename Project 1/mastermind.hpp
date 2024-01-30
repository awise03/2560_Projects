/*
    * Code.h
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/

#ifndef MASTERMIND.HPP
#define MASTERMIND.HPP

#include "Code.hpp"
#include "response.hpp" 

using namespace std;

class Mastermind
{ 
    public:
    Mastermind(int n, int m);
    Mastermind(); //defult constructur with default values for n and m
    void PrintSecret();
    Code humanGuess() const;
    response getResponse(const Code &g1) const;
    bool isSolved(const response &r1)const;
    void playGame();

    private:
    Code secretCode;
};



#endif