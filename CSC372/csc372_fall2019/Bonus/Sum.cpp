#include "Sum.h"

Sum::Sum( vector<int> nums, int N, int TestNum )
{
    this->N = N;
    this->nums = nums; 
    this->TestNum = TestNum;
}

// Algorithm gotten from https://www.youtube.com/watch?v=Y0ZqKpToTic 
void Sum::operation( int N ) 
{ 
    min.first = 99999;
    createStorage();
    
    for( int i = 0; i < nums.size(); ++i )
    {
        for( int j = 0; j < N + 1; ++j )
        {
        
        // GRADING: STORAGE
            if( j - rows[i] >= 0 )
            {
                // GRADING: CALC
                storage[ i ][ j ] = ( storage[ i ][ j - rows[ i ] ] ) + 1;
            }

            else if( i == 0 )
                storage[ i ][ j ] = j % rows[i];
            
            // GRADING: CALC
            else
                storage[ i ][ j ] = storage[ i-1 ][ j ];    
            
            // Keeping track of the best solution.
            if( j == N )
            {
                if (storage[i][j] < min.first)
                {
                    min.first = storage[i][j];
                    min.second = i;
                }
            }
        }
    }
    
    findSolution();
    printSolution();
}

void Sum::findSolution()
{
    int temp;
    int j = N;
    int i = min.second;
    
    do
    {
        if( j - rows[i] >= 0 ) 
        {
            solutions.push_back( rows[i] );
            
            j = j - rows[i];
        }

        else
            i = i - 1;
       
        
    }while( i >= 0 );
}

void Sum::createStorage()
{
    int size = nums.size();
    storage = new ( nothrow ) int*[ size + 1 ];

    for( int i = 0; i < nums.size(); ++i )
        storage[i] = new ( nothrow ) int[ N ];

    
    for( int i = 0; i < size; ++i )
    {
        for( int j = 0; j < N+1; ++j )
            storage[i][j] = 99;
    }

    // Maps the rows of storage to the actual values in nums vector.
    for( int i = 0; i < nums.size(); ++i )
    {
        rows[i] = nums[i];
    }
}

void Sum::printSolution( )
{
   cout << "Test " << TestNum << endl 
       << "Input: s = {";
   for (int i = 0; i < nums.size(); ++i)
   {
       cout << nums[i];
       if( i != nums.size() - 1 )
           cout << ", ";
   }

   cout << "} n = " << N << endl 
       << "Min Count: " << min.first << endl
       << "Result: ";

   for( int i = solutions.size() - 1; i >= 0; --i )
        cout << solutions[i] << " ";

   cout << endl << "================================================" << endl;
}