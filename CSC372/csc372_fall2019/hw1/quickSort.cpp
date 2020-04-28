#include"quickSort.h"

int QuickSort::partition( vector<int> &arr, int firstIndex, int lastIndex )
{
    int pivot = arr[lastIndex];
    int i = firstIndex - 1;

    for( int j = firstIndex; j < lastIndex; ++j )
    {
        if( arr[j] <= pivot )
        {
            ++i;
            swap( arr[i], arr[j] );
        }
    }

    swap( arr[i+1], arr[lastIndex] );
    return i + 1;
}

/******************************************************
GRADING: QUICK
******************************************************/
void QuickSort::Sort( vector<int> &arr, int firstIndex, int lastIndex )
{
    int currentIndex;

    if( firstIndex < lastIndex )
    {
        currentIndex = partition( arr, firstIndex, lastIndex );
        Sort( arr, firstIndex, currentIndex - 1);
        Sort( arr, currentIndex + 1, lastIndex );
    }
}