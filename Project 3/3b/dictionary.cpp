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
    } else {
        cout << "Error opening file" << endl;
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
        cout << words[i] << endl;
    }
}

void Dictionary::quicksort(int min, int max) {
    if(min < max) {
        int part = partition(min, max);

        quicksort(min, part - 1);
        quicksort(part + 1, max);
    }

    
}

int Dictionary::partition(int min, int max) {
    string pivot = words[max];

    int i = min - 1;

    for(int j = min; j < max; j++) {
        if(words[j] < pivot) {
            i++;
            swap(words[i], words[j]);
        }
    }
    swap(words[i + 1], words[max]);
    return (i + 1);
}


// Returns the index of the word we are searching for
int Dictionary::binarySearch(const string& key) const {
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

int Dictionary::getDictSize() const {
    return words.size();
}

vector<string> Dictionary::getWords() const {
    return words;
}