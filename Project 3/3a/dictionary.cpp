#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Reads the elements within the dictionary and adds them to the words vector
void Dictionary::readDict(const string& filename) {
    ifstream file(filename);
    if(file.is_open()) {
        string word;
        while(getline(file, word)) {
            words.push_back(word);
        }

        file.close();
    }
}

// Prints all elements within the dictionary
void Dictionary::printDict() {
    for(int i = 0; i < words.size(); i++) {
        cout << words[i] << endl;
    }
}

// Sorts the dictionary using selection sort
void Dictionary::selectionSort() {
    for(int i = 0; i < words.size(); i++) {
        int minIndex = i;

        for(int j = i + 1; j < words.size(); j++) {
            if(words[j] < words[minIndex]) {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            swap(words[i], words[minIndex]);
        }
    }
}

// Returns the index of the word we are searching for
int Dictionary::binarySearch(const string& key) {
    int left = 0; 
    int right = words.size() - 1;

    while(left <= right){
        int mid = left + (right - left) / 2;
        if(words[mid] == key){
            return mid;
        } else if (words[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}