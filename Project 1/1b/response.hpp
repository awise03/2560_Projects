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

        int getCorrectVal() const;
        int getIncorrectPos() const;

        void setCorrectVal(int);
        void setIncorrectPos(int);

        friend bool operator==(const response &r1, const response &r2);
        friend ostream & operator<<(ostream &out, const response &r1);
};


#endif