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

        void quicksort(int min, int max);
        int partition(int min, int max);

        int binarySearch(const string& key) const;
        int getDictSize() const;
};

#endif
