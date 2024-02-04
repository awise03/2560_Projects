/*
    * mastermind.hpp
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/

#ifndef MASTERMIND_HPP
#define MASTERMIND_HPP

#include "code.hpp"
#include "response.hpp" 

using namespace std;

class Mastermind
{ 
    public:
        Mastermind(int n, int m);
        Mastermind(); //defult constructur with default values for n and m
        
        void PrintSecret();
        Code humanGuess();
        response getResponse(const Code g1);
        
        bool isSolved(response r1);
        void playGame();
        

    private:
        Code secretCode;
};



#endif