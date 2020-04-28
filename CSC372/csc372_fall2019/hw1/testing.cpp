#include "testing.h"

void printVector( vector<int> arr )
{
    for( int i = 0; i < arr.size(); ++i )
    {
        cout << arr[i];
        
        if( i < arr.size() - 1 )
            cout << ", ";
    }
     
    cout << endl;
}

/******************************************************
Template function for running correctness tests
GRADING: CORRECTNESS TESTS
******************************************************/
void correctness() 
{
    vector<int> test1 = { 2,1 };
    vector<int> test2 = { 1, 3, 2 };
    vector<int> test3 = { 2, 2, 1, 3, 5, 4, 8, 0 };
    vector<int> test4 = { 99, 33, 2, 7, 1, 3, 0, 8, -1 };
    HeapSort heap;
    QuickSort quick;

    cout << "Test 1: Basic sort with 2 elements" << endl;
    cout << "Original: 2, 1" << endl;
    
    cout << "Quick Result: ";
    vector<int> test1Copy = test1;
    quick.Sort( test1Copy, 0, test1Copy.size() - 1 );
    printVector( test1Copy  );
    
    if( makeSureItsSorted( test1Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;

    cout << "Heap Result: ";
    test1Copy = test1;
    heap.Sort( test1Copy );
    printVector( test1Copy );

    if( makeSureItsSorted( test1Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;
    
    cout << endl << endl;

    cout << "Test 2: Basic sort with 3 elements" << endl;
    cout << "Original: 1, 3, 2" << endl;
    
    cout << "Quick Result: ";
    vector<int> test2Copy = test2;
    quick.Sort( test2Copy, 0, test2Copy.size() - 1 );
    printVector( test2Copy );

    if( makeSureItsSorted( test2Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;

    cout << "Heap Result: ";
    test2Copy = test2;
    heap.Sort( test2Copy );
    printVector( test2Copy );

    if( makeSureItsSorted( test2Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;
    
    cout << endl << endl;

    cout << "Test 3: Basic sort with even # of elements" << endl;
    cout << "Original: 2, 2, 1, 3, 5, 4, 8, 0 " << endl;
    cout << "Quick Result: ";
    vector<int> test3Copy = test3;
    quick.Sort( test3Copy, 0, test3Copy.size() - 1 ); 
    printVector( test3Copy );

    if( makeSureItsSorted( test3Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;
    
    cout << "Heap Result: ";
    test3Copy = test3;
    heap.Sort( test3Copy );
    printVector( test3Copy );

    if( makeSureItsSorted( test3Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;

    cout << endl << endl;

    cout << "Test 4: Basic sort with odd # of elements" << endl;
    cout << "Original: 99 33 2 7 1 3 0 8 -1 "  << endl; 
    cout << "Quick Result: ";
    
    vector<int> test4Copy = test4;
    quick.Sort( test4Copy, 0, test4Copy.size() - 1 );
    printVector( test4Copy );

    if( makeSureItsSorted( test4Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;
    
    cout << "Heap Result: ";
    test4Copy = test4;
    heap.Sort( test4Copy );
    printVector( test4Copy );

    if( makeSureItsSorted( test4Copy ) )
        cout << "Passed!" << endl;

    else
        cout << "Failed!" << endl;

}

void timeSorts()
{
    vector<int> numbers;
    vector<int> numbersCopy;
    HeapSort heap;
    QuickSort quick;
    int width = 20;

    clock_t startTime, endTime;
    clock_t averageTime = 0;
    int arr[11] = { 10, 20, 50, 100, 200, 500, 1000, 10000, 100000, 1000000, 2000000 };

    cout << "Size" << setw( width ) << "QuickSort Average" << setw( width ) << "HeapSort Average" << endl
        << setw( width ) << "Time(ms)" << setw( width ) << "Time(ms)" << endl;

    for (int i = 0; i < 11; ++i)
    {
        numbers = fillVectorWithRandom( arr[i] );
        for (int i = 0; i < 3; ++i)
        {
            numbersCopy = numbers;
            startTime = clock();
            quick.Sort(numbersCopy, 0, numbersCopy.size() - 1);
            endTime = clock();

            averageTime += endTime - startTime;
        }
        
        width = getColumnWidth( arr[i] );

        averageTime = int( averageTime / 3 );
   
        cout << arr[i] << setw( width ) << averageTime;

        averageTime = 0;

        for (int i = 0; i < 3; ++i)
        {
            numbersCopy = numbers;
            startTime = clock();
            heap.Sort(numbersCopy);
            endTime = clock();

            averageTime += endTime - startTime;
        }

        averageTime = int( averageTime / 3 );

        cout << setw( 20 ) << averageTime << endl;
    }
}

vector<int> fillVectorWithRandom( int size )
{
    vector<int> random;
    srand( time( NULL ) );

    for( int i = 0; i < size; ++i )
        random.push_back ( rand( ) );

    return random;
}

int getColumnWidth( int size )
{
    int width = 20;

    if( size < 100 )
        width = width;

    else if( size < 1000 )
        width -= 1;

    else if( size < 10000 )
        width -= 2;

    else if( size < 100000 )
        width -= 3;

    else if( size < 1000000 )
        width -= 4;
    else
        width -= 5;

    return width;
}

bool makeSureItsSorted( vector<int> arr )
{
    for( int i = 0; i < arr.size() - 1; ++i )
    {
        if( arr[i] > arr[i + 1] )
            return false;
    }

    return true;
}