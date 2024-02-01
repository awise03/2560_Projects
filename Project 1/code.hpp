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
        Code(int, int);

        void randomInitial();

        int checkCorrect(const Code&g1);
        int checkIncorrect(const Code&g2);

    private:
        int n, m;
        vector<int> secretCode;
};

#endif