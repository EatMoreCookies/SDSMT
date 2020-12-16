/***************************************************************************//**
 * @file 
 * @brief demonstrates the bubble sort, insertion sort, and selection sort
 *
 * @mainpage Lab 1 - Doxygen Verification
 *
 * @section course_section Course Information
 *
 * @authors Fred Flintstone
 *
 * @date January 31, 2012
 *
 * @par Instructor:
 *         Dr. Slate
 *
 * @par Course:
 *         CSC 150 - Section 1 - 2:00 pm
 *
 * @par Location:
 *         McLaury - Room 313
 *
 * @section program_section Program Information
 *
 * @details This program will make 3 identical arrays using a random number
 * generator. The  function rand returns a number between 0 and 32,767.  This
 * number is then copied into the first location of the three arrays.  Then
 * another number is generated and put into the second location of the arrays.
 * Calls to rand will keep being made until all spots are filled in the arrays.
 * The size of the arrays are provided with the global constant SIZE.
 *
 * After the arrays are filled, we will pass one array to a function that will
 * sort the array using the bubble sort method.  Upon return from this a
 * function will verify that the array was sorted.  If it was not sorted, the
 * program will exit.
 *
 * Because of space, the rest of the details have been omitted.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe
   d:\> c:\bin\prog3.exe
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  The isSorted routine has a problem if the first element is not
 * in order (not really though).
 * @bug  Sometimes the arrays fill up with all the same values (not really)
 *
 * @todo Finish documenting with doxygen tags
 * @todo Write a function to generate true random 32 bit integers
 * @todo Modify main to use this new random function
 * @todo Write the code in main to write the arrays out to a file.
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  ---------------------------------------------------------------
   Jan  1, 2011  Started writing the sorts
   Jan 15, 2011  Wrote the isSorted function and found the fictitious  error.
                 Need to generate test cases with the first and last element
                 being out of order.
   Jan 18, 2011  Genereate the random arrays to be sorted.
   Jan 19, 2011  Started learning doxygen
   @endverbatim
 *
 ******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*******************************************************************************
 *             Constant Variables, defines and Enums
 ******************************************************************************/
/*!
 * @brief How many elements in array
 */
const int SIZE = 1000;



/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/
bool isSorted ( int arr[], int arraySize );
void bubbleSort ( int arr[], int arraySize );
void insertionSort ( int arr[], int arraySize );
void selectionSort ( int arr[], int arraySize );



/***************************************************************************//**
 * @author Fred Flintstone
 *
 * @par Description:
 * This is the starting point to the program.  It will retreive a
 * number form the rand function and place it into three arrays.  Each
 * array will then be sorted using one of three sort techniques,
 * bubble, insertion, and selection.  Upon returning from each sort
 * function the sorted array will then be verified using the isSorted
 * function.  If the array is not in order, a message will be
 * outputted and an error number will be returned.
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 1 bubble sort failed
 * @returns 2 insertion sort failed
 * @returns 3 selection sort failed
 *
 ******************************************************************************/
int main ( int argc, char **argv )
{
    int i;
    int num;

    int barray[SIZE];           // an integer array for the bubble sort
    int iarray[SIZE];           // an integer array for the insertion sort
    int sarray[SIZE];           // an integer array for the selection sort

    // initialize the c++ random number generator
    srand ( ( int ) time ( NULL ) );

    // call the random number generator to retreive a random number
    // then place the random number in all three arrays
    // this will create 3 identical arrays with the same random numbers.
    for ( i = 0; i < SIZE; i++ )
    {
        num = rand();
        barray[i] = num;
        iarray[i] = num;
        sarray[i] = num;
    }

    // call the bubble sort routine to sort the barray
    // upon return, check that the array was correctly sorted
    // if not output error message and exit program.
    bubbleSort ( barray, SIZE );
    if ( !isSorted ( barray, SIZE ) )
    {
        cout << "The array did not get sorted using bubble sort." << endl;
    }
	else
	{
		cout << "Bubble sort worked correctly" << endl;
	}

    // call the insertion sort routine to sort the barray
    // upon return, check that the array was correctly sorted
    // if not output error message and exit program.
    insertionSort ( iarray, SIZE );
    if ( !isSorted ( iarray, SIZE ) )
    {
        cout << "The array did not get sorted using insertion sort." << endl;
    }
	else
	{
		cout << "Insertion sort worked correctly" << endl;
	}


    // call the selection sort routine to sort the barray
    // upon return, check that the array was correctly sorted
    // if not output error message and exit program.
    selectionSort ( sarray, SIZE );
    if ( !isSorted ( sarray, SIZE ) )
    {
        cout << "The array did not get sorted using selection sort." << endl;
    }
	else
	{
		cout << "Selection sort worked correctly" << endl;
	}


    return 0;
}


/***************************************************************************//**
 * @author Barney Rubble
 *
 * @par Description:
 * This function receives an array and will process the array placing
 * the elements in order using the bubble sort method.  It moves
 * through the array comparing adjacent items and swapping the
 * elements if they are not in order.  It will make n number of
 * passes.  If it makes a complete pass without swapping two
 * elements, the array is in order and no further processing is
 * required.
 *
 * @param[in,out] arr - the array to be processed.
 * @param[in] arraySize - the number of elements in the array.
 *
 * @returns none
 ******************************************************************************/
void bubbleSort ( int arr[], int arraySize )
{
    int i, j;
    bool swapMade;        // variable to track if a swap was made during a pass

    // make n-1 passes through the data array moving the largest value
    // towards the end
    for ( i = 0; i < arraySize - 1; i++ )
    {
        // assume no swap has been made
        swapMade = false;

        // move the largest element towards the end
        for ( j = 0; j < arraySize - i - 1; j++ )
        {
            // if element is larger than the next element
            // swap and set the tracking variable to true
            // to indicate a swap was made.
            if ( arr[j] > arr[j + 1] )
            {
                swapMade = true;
                swap ( arr[j], arr[j + 1] );
            }
        }

        // if no swap has been made, list is in order
        // and we can return leave the function
        if ( !swapMade )
            return;
    }
}


/***************************************************************************//**
 * @author Fred Flintstone
 *
 * @par Description:
 * Will shift elements up in the sorted half of the array as long
 * as the item is larger than the item being inserted.  Once it
 * encounters an item that is <= to the number being inserted, it
 * will stop shifting and insert the item into the vacated spot.
 * this will happen n number of times in order to insert n items
 * into the array.
 *
 * @param[in,out] arr - the array to be processed.
 * @param[in] arraySize - the number of elements in the array.
 *
 * @returns none
 ******************************************************************************/
void insertionSort ( int arr[], int arraySize )
{
    int i, j;
    int iValue;

    // the first element is in place, insert the remaining
    // elements into the list.
    for ( j = 1; j < arraySize; j++ )
    {
        // save the next element to be inserted
        iValue = arr[j];
        i = j - 1;

        // travers backwards through the numbers that are in order
        // moving any element that is greater than iValue down.
        // Stop when you understep the array or it is less than or
        // equal to the number being inserted.
        while ( arr[i] > iValue && i >= 0 )
        {
            arr[i + 1] = arr[i];
            i--;
        }

        // place our value into the sorted portion of the array.
        arr[i + 1] = iValue;
    }
}


/***************************************************************************//**
 * @author Barney Rubble
 *
 * @par Description:
 * This function receives an array and will process the array looking
 * for any values that are out of order.  The numbers in the array
 * should be ascending order to pass the test.
 *
 * @param[in] arr - the array to be processed.
 * @param[in] arraySize - the number of elements in the array.
 *
 * @returns true - the entire array is in ascending order
 * @returns false - the array is not in ascending order
 ******************************************************************************/
bool isSorted ( int arr[], int arraySize )
{
    int i;

    // traverse through the array comparing element i to element i+1
    // if element i is larger, the array is not in ascending order
    // and we should return false.  If the array is in order,
    // return true
    for ( i = 0; i < arraySize - 1; i++ )
    {
        if ( arr[i] > arr[i + 1] )
            return false;
    }

    return true;
}


/***************************************************************************//**
 * @author Fred Flintstone
 *
 * @par Credits:
 *    <a href="http://sdmines.sdsmt.edu/sdsmt/directory/personnel/alogar">
 *    Dr. Antonette Logar</a>
 *    gave us this code in CSC 150. A copy of the code can be found
 *    <a href="http://www.mcs.sdsmt.edu/csc150">here.</a>
 *
 * @par Description:
 * This function receives an array and will process the array placing
 * the elements in order using the insertion sort method.  It moves
 * through the array finding the location of the smallest item in
 * the list and swapping the elements if they are not in order.
 * It will make N number of passes doing this where N is the size
 * of the list
 *
 * @param[in,out] arr - the array to be processed.
 * @param[in] arraySize - the number of elements in the array.
 *
 * @returns none
 ******************************************************************************/
void selectionSort ( int arr[], int arraySize )
{
    int i, j;
    int smallestIndex;

    // make n-1 passes through the array finding
    // the smallest and then the next smallest element
    // in the array and moving it into place.
    for ( i = 0; i < arraySize - 1; i++ )
    {
        // assume this is the smallest element out of remaining
        // elements in the array.
        smallestIndex = i;

        // traverse through all the remaining number looking
        // for a smaller number than the one at the array spot
        // smallest index.
        for ( j = i + 1; j < arraySize; j++ )
        {
            // if an element is less than it, store its index
            if ( arr[j] < arr[smallestIndex] )
            {
                smallestIndex = j;
            }
        }

        // swap the smallest element into position
        swap ( arr[i], arr[smallestIndex] );
    }
}


