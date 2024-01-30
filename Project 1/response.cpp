#include <iostream>
#include "response.hpp"

response::response(){
    n = 5;
    m = 10;
}

response::response(int length, int range){
    n = length;
    m = range;
}

bool response::operator==()