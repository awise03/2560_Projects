#include <iostream>
#include <vector>
using namespace std;

#ifndef HEAP_H
#define HEAP_H

template <class T> 

class Heap {
    private:
        vector<T> data;
        int heapsize;
        int parent(const int &index);
        int left(const int &index);
        int right(const int &index);

    public:
        T getItem(const int &index);
        vector<T> heapsort();
        void maxHeapify(const int &index);
        void buildMaxHeap(const vector<T> &dict);
};

#endif