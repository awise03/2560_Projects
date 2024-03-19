//
// Created by Alexander Wise and Jackymora Isa on 3/17/24.
//

#include "heap.h"

// Returns the parent of an index
template<class T>
int Heap<T>::parent(const int &index) {
    return (index / 2);
}

// Returns the right branch of an index
template<class T>
int Heap<T>::right(const int &index) {
    return (index * 2) + 1;
}

// Returns the left branch of an index
template<class T>
int Heap<T>::left(const int &index) {
    return (index * 2);
}

// Initializes the max heap
template<class T>
void Heap<T>::initializeMaxHeap(const vector<T> &dict) {
    data = dict;
    // Sets the first element to an empty string
    data.push_back(data[0]);
    data[0] = " ";

}

// Builds the heap
template<class T>
void Heap<T>::buildMaxHeap(){
    // Sets heapsize value
    heapsize = data.size();
    // Applies maxHeapify to half of the elements
    for(int i = heapsize / 2; i > 0; i--){
        maxHeapify(i);
    }
}

// maxHeapify function to ensure the max Heap property is maintined 
template<class T>
void Heap<T>::maxHeapify(const int &index) {
    // Initialize left, right, and largest index values
    int l = left(index);
    int r = right(index);
    int largest = index;

    // Changes value of largest if left is greater
    if(l <= heapsize && data[l] > data[largest]) {
        largest = l;
    }

    // Changes value of largest if right is greater
    if(r <= heapsize && data[r] > data[largest]) {
        largest = r;
    }

    // Swaps and recursviley calls if the largest value is not already in the correct location
    if(largest != index) {
        swap(data[index], data[largest]);
        maxHeapify(largest);
    }
}

// Sorts the heap using heapsort
template <class T>
vector<T> Heap<T>::heapsort() {
    // Iterates through each value within the heap
    for(int i = heapsize; i > 1; i--) {
        // Swaps first element and the ith element
        swap(data[1], data[i]);
        heapsize--;
        // Applies heapify to the new first element
        maxHeapify(1);
    }
    // Returns the sorted heap vector. 
    return data;
}
