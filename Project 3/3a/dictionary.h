//
// Created by Alexander Wise and Jackymora Isa on 3/6/24.
//

#include <iostream>


#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
using namespace std;

class Dictionary {
    private: 
        vector<string> words;

    public:
        vector<string> getWords() const;
        void readDict(const string& filename);
        void printDict();
        void selectionSort();
        int binarySearch(const string& key) const;
        int getDictSize() const;
};

#endif
