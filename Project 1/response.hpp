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
        int n, m;
    public:
        response();
        response(int n, int m);

        bool operator==(response &r1);
        bool operator<<(response &r1);
};


#endif