#include <iostream>


#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
using namespace std;

class Dictionary {
    private: 
        vector<string> words;
        

    public:
        void readDict(const string& filename);
        void printDict();
        void selectionSort();
        int binarySearch(const string& key);
};

#endif
