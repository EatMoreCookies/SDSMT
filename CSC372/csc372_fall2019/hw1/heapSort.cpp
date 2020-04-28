#include"heapSort.h"

/******************************************************
GRADING: HEAP
******************************************************/
void HeapSort::Sort( vector<int> &arr )
{
    buildMaxHeap( arr ); 
    
    for( int i = arr.size() - 1; i >= 1; --i )
    {
        swap( arr[0], arr[i] );

        --this->heapSize;
        
        maxHeapify( arr, 0 );
    }
}

void HeapSort::buildMaxHeap( vector<int> &arr )
{
    this->heapSize = arr.size();

    for( int i = floor( ( arr.size() - 1 ) / 2 ); i >= 0; --i )
    {
        maxHeapify( arr, i );
    }
}

void HeapSort::maxHeapify(vector<int> &arr, int index )
{
    int largest;
    int l = left( index );
    int r = right( index );

    if( l <= this->heapSize - 1 && arr[l] > arr[index] )
        largest = l;
    else
        largest = index;

    if ( r <= this->heapSize - 1 and arr[r] > arr[largest] )
        largest = r;
    
    if( largest != index )
    {
        swap( arr[index], arr[largest] );
        maxHeapify( arr, largest );
    }
    
}

int HeapSort::parent( int index )
{
    return floor( index / 2 );
}

int HeapSort::left( int index )
{
    return 2 * index; 
}

int HeapSort::right( int index )
{
    return 2 * index + 1;
}