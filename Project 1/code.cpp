#include <iostream>
#include "code.hpp"
#include <random>

//initialize code object that passes values n and m via code constructor
Code::Code(int n, int m)
{
    randomInitial(n,m); // code object
}

void Code::randomInitial(int n, int m)
{
    // creates sequence of digits from 0 to m-1
    std::vector<int> digits;
    for (int i = 0; i < m; i++)
    {
        digits.push_back(i);
    }

    //seed of random number generator is based on current time
    std::srand(static_cast<unsigned int>(std::time(0)));

    //performs random number generation and shuffles vector elements
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(digits.begin(), digits.end(),rng);

    // Takes first n digit as begining of secret code
    secretCode.assign(digits.begin(),digits.begin() + n);
}
