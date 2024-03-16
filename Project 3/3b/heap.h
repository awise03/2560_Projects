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

    public:
        int parent(const int &index);
        int left(const int &index);
        int right(const int &index);
        T getItem(const int &index);
};

#endif