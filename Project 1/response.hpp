/*
    * response.hpp
    * Created on: Jan 30th
    *       Author: Jacky and Alex
    * 
*/


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
using namespace std;

class response {
    private:
        int correctVal, incorrectPos;
    public:
        response(int c, int i);

        int getCorrectVal();
        int getIncorrectPos();

        void setCorrectVal(int);
        void setIncorrectPos(int);

        bool operator==(const response &r1);
        friend ostream & operator<<(ostream&out, const response &r1);
};


#endif