//
// Created by Alexander Wise and Jackymora Isa on 3/14/24.
//


#include "dictionary.h"
#include "heap.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Reads the elements within the dictionary and adds them to the words vector
void Dictionary::readDict(const string& filename) {
    // File object with name of file to open
    ifstream file(filename);
    if(file.is_open()) {
        string word;
        // Adds word to vector while there is a word on the next line
        while(getline(file, word)) {
            words.push_back(word);
        }
        // Close file when finished
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
    // Iterates through each element in the dictionary
    for(int i = 0; i < words.size(); i++) {
        int minIndex = i;
        // Iterates through each element from i to the end
        for(int j = i + 1; j < words.size(); j++) {
            // Looks to see if current value is greater than min value 
            if(words[j] < words[minIndex]) {
                minIndex = j;
            }
        }
        // Swaps min value with i if they are not the same index
        if(minIndex != i) {
            swap(words[i], words[minIndex]);
        }
    }
}

// Returns the index of the word we are searching for
int Dictionary::binarySearch(const string& key) const {
    int left = 0; 
    int right = words.size() - 1;

    // Moves from left to right
    while(left <= right){
        // Midpoint is between the right and left pointers
        int mid = left + (right - left) / 2;

        // Return mid if found at mid
        if(words[mid] == key){
            return mid;

        // ignore the left half if the key is greater
        } else if (words[mid] < key) {
            left = mid + 1;

        // Ignore the right half if the key is smaller    
        } else {
            right = mid - 1;
        }
    }
    // Return -1 if not found
    return -1;
}

// Returns dictionary size
int Dictionary::getDictSize() const {
    return words.size();
}

// Returns the vector
vector<string> Dictionary::getWords() const {
    return words;
}

// Quicksort algorithm 
void Dictionary::quicksort(int min, int max) {
    // Will only enter if the range is valid
    if(min < max) {
        // Partion array and get index of partion 
        int part = partition(min, max);

        // Recursively apply quickosrt to left and right partitions. 
        quicksort(min, part - 1);
        quicksort(part + 1, max);
    }
}

// Funtion to set a partion position 
int Dictionary::partition(int min, int max) {
    // Set the pivot to the max value
    string pivot = words[max];

    int i = min - 1;

    // Iterate through the range of min to max - 1
    for(int j = min; j < max; j++) {
        // swaps partition index and current index if value at j is less than pivot
        if(words[j] < pivot) {
            i++;
            swap(words[i], words[j]);
        }
    }
    // Swaps pivot with element at index i + 1
    swap(words[i + 1], words[max]);
    // Returns the index where pivot is placed
    return (i + 1);
}

// Sorts dictionary using heapsort
void Dictionary::heapsort() {
    // Initialize new heap object
    Heap<string> h1;

    // Initialize the max heap using the unsorted dictionary 
    h1.initializeMaxHeap(words);

    // Builds the maxHeap 
    h1.buildMaxHeap();

    // Sorts using heapsort
    words = h1.heapsort();
}