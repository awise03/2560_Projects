#include <iostream>
#include "mastermind.hpp"

// user-based input constructor
Mastermind::Mastermind(int n, int m):secretCode(n,m)
{
    std::cout << "Enter The code length (n)" <<endl;
    std::cin >> n;

    std:: cout << "Enter the range of digits" << endl;
    std::cin >>m;
}

//Default constructor with default values of code length (n) and digit range (m)
Mastermind::Mastermind():secretCode(5,10)
{};

void Mastermind::PrintSecret()
{
    std::cout<< "The secret code: ";

}
