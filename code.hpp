/*
    * Code.h
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/


#ifndef CODE.HPP
#define CODE.HPP

using namespace std;
#include <vector>

class Code
{
    public:
    Code(int n, int m);
    void randomInitial();
    int checkCorrect(const Code&g1);
    int checkIncorrect(const Code&g2);
    


    private:
    vector<int> secretCode;
};

#endif