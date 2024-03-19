//
// Created by Alexander Wise and Jackymora Isa on 3/17/24.
//

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
        void initializeMaxHeap(const vector<T> &dict);
        T getItem(const int &index);
        vector<T> heapsort();
        void maxHeapify(const int &index);
        void buildMaxHeap();
};

#endif