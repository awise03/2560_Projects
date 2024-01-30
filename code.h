/*
    * Code.h
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/


#ifndef CODE.H
#define CODE.H

#include <vector>

class Code
{
    public:
    Code(int n, int m);
    void randomInitial();
    int checkCorrect(const vector<int> &guess);
    int checkIncorrect(const vector<int> &guess);



    private:
     
}


#endif