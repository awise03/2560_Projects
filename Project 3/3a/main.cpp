#include "dictionary.cpp"
#include "grid.cpp"
#include <iostream>

using namespace std;

int main() {
    Dictionary dict;
    dict.readDict("dictionary-2");
    dict.printDict();
    dict.selectionSort();


    return 0;
}