/******************************************************//*
* Nathaniel Fagrey.
* CSC 372. HW 1.
*
* Compiler Version: Visual C++ 14.1
********************************************************/
#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <chrono>
#include "testing.h"
#include "quickSort.h"
#include "heapSort.h"
using namespace std;

int main() 
{
    char choice = 'c';
    vector<int> input;
    int userInput;
    HeapSort heap;
    QuickSort quick;
    vector<int> copy;

    while (toupper(choice) != 'Q') {
        cout << "\nEnter T to run correctness tests\n"
             << "Enter U to run accept user input\n"
             << "Enter E to run time tests\n" << endl
             << "Enter Q to quit" << endl;

        cout << "Choice: ";
        cin >> choice;

        if (toupper(choice) == 'T') {
            correctness();
        } else if (toupper(choice) == 'E') {
            timeSorts();

        } else if (toupper(choice) == 'U') {
            cout << "Input ( # # # ... -999): ";

            while( cin >> userInput && userInput != -999 )
                input.push_back( userInput);
            
            copy = input;
            quick.Sort( copy, 0, input.size() - 1 );
            cout << "Quick: ";
            printVector( copy );
            
            copy = input;
            heap.Sort( copy );
            cout << "Heap: ";
            printVector( copy );
        }
    }

    return 0;
}