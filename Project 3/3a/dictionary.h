#include <iostream>


#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
using namespace std;

class Dictionary {
    private: 
        vector<string> keys;
    public:
        void readDict();
        void printDict();
        void selectionSort();
        void binarySearch();
};

#endif
