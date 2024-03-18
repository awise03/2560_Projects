#include "heap.h"

template<class T> 
int Heap<T>::parent(int const &index) {
    return (index/2);
}

template<class T> 
int Heap<T>::right(const int &index) {
    return (index*2 + 1);
}

template <class T> 
int Heap<T>::left(const int &index) {
    return (index * 2);
}

template <class T> 
T Heap<T>::getItem(int const &index) { 
    return data[index];
}

template <class T> 
void Heap<T>::maxHeapify(const int &index) {
    int l = left(index);
    int r = right(index);
    int largest = index;

    if(left <= data.size() && data[left] > data[largest]) {
        largest = left;
    } 

    if(right <= data.size() && data[right] > data[largest]) {
        largest = right;
    }

    if(largest != index) {
        swap(data[index], data[largest]);
        maxHeapify(largest);
    }

}

template <class T>
void Heap<T>::buildMaxHeap(const vector<T> &dict) {
    heapsize = dict.size();
    data = dict;
    data.push_back(data[0]);
    data[0] = " ";

    for(int i = heapsize / 2; i > 0; i--) {
        maxHeapify(i);
    }
}

template <class T> 
vector<T> Heap<T>::heapsort() {
    for(int i = heapsize / 2; i > 2; i--) {
        swap(data[1], data[i])
        maxHeapify(i)
    }
}