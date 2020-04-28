#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class HeapSort
{
    public:
        void Sort( vector<int> &arr );
        void buildMaxHeap( vector<int> &arr );
        void maxHeapify( vector<int> &arr, int index );

    private:
        int heapSize = 0;
        int parent( int index );
        int left( int index );
        int right( int index );
};

#endif 



