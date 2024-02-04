/*
    * Code.hpp
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/


#ifndef CODE_HPP
#define CODE_HPP

#include <vector>
using namespace std;


class Code
{
    public:
        // Code Constructors
        Code(int m, int n);
        Code(vector<int>&);

        void randomInitial();
        void printCode();

        int checkCorrect(const Code&g1) const;
        int checkIncorrect(const Code&g2) const;
        
        int getSize() const;
        int getRange() const;

        vector<int> getCode();

    private:
        int n, m;
        vector<int> secretCode;
};

#endif