/*
    * Code.h
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/


#ifndef CODE.HPP
#define CODE.HPP

#include <vector>

class Code
{
    public:
    Code(int n, int m);
    void randomInitial(int n, int m);
    int checkCorrect(const Code&g1)const;
    int checkIncorrect(const Code&g2)const;
    


    private:
    std::vector<int> secretCode;

};

#endif