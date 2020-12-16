/*-------------------------------------------------------------------
Program: lab14_2.cpp
Author: MCS/SDSM&T
Course: CSC 150 - Section M000
Instructor: A Instructor
Date: 12/07/2010
Description:
Reads a file containing student identifiers and runtimes for a program.
Stores the data to a 2D array. Allows user to look up individual student
results.


---------------------------------------------------------------------
Includes
---------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
using namespace std;


//-------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------
int search(int scores[][2], int num, int id);

void sort(int run_data[][2]);



/********************************************************************
Function:      main
Description:   Program entry/exit point, reads data file, prompts for inputs, 
displays results
Parameters:    none
Returns:       0
*********************************************************************/
int main()
{
    int student;   // input ID
    int index;     
    int run_data[300][2] = { 0 };
    int num = 0;  //number of students read

    bool done = false;  //flag to end main loop

    ifstream fin;

    fin.open( "runtimes.txt" );
    if( !fin )
    {
        cout << "Error opening data file. Exiting." << endl;
        return -1 ;
    }

    while( num < 300 && fin >> run_data[num][0] )
    {
        fin >> run_data[num][1];
        num++;
    }

    fin.close( );
    

	sort(run_data);

    
    cout << "Enter student ID: ";

    while ( !done && cin >> student )
    {
        //  Test for end of the program 
        if (student == 0)
        {
            cout << "End of Program!" << endl;
            done = true;
        }

        else
        {

            // Call search function to find student index
            index = search (run_data, 300, student );

            // Display error if not found, otherwise ID and runtime
            if (index == -1)
                cout << "Student not found!" << endl;
            else
                cout << "Student: " << student << " had runtime of: " 
                << run_data[index][1] << " seconds" << endl; 

            // prompt for another student
            cout << "Enter student ID: ";
        }

    }

    return 0;
}


/********************************************************************
Function: search
Author: MCS/SDSM&T
Description:
This function searches a 2-D array for match in the
first column, returning the index if found or -1 if not.
Parameters:  scores: 2-D array of int
num: int, number of rows in scores array
id: int, a value to search for
Returns      index of found item, -1 if not found
********************************************************************/

int search(int scores[][2], int num, int id)
{
    int left;
    int mid;
    int right;

    left = 0;
    right = num - 1;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (scores[mid][0] == id)
            return mid;
        if (scores[mid][0] > id)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

/********************************************************************
Function: sort
Author: MCS/SDSM&T
Description:
This function sorts a 2-D array based on the first column, maintaining
    the association of the two columns' data.

Parameters:  


Returns      
********************************************************************/
void sort(int run_data[][2])
{
	int i, j = 0;
	int temp_rows, temp_cols = 0;
	
	for (j = 0; j < 300 - 1; ++j)
	{
		for (i = 0; i < 300 - j - 1; ++i)
		{
			if (run_data[i][0] > run_data[i + 1][0])
			{
				temp_rows = run_data[i + 1][0];

				run_data[i + 1][0] = run_data[i][0];

				run_data[i][0] = temp_rows;

				
				temp_cols = run_data[i + 1][1];

				run_data[i + 1][1] = run_data[i][1];

				run_data[i][1] = temp_cols;
			
				
			}
		
		}
	}
	for (i = 0; i < 300; ++i)
	{
		cout << run_data[i][0] << endl;
	}
	
}
