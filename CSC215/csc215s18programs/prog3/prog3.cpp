/*************************************************************************//**
 * @file 
 *
 * @mainpage Program 3 - The Knight's Tour
 * 
 * @section course_section Course Information 
 *
 * @author Nathaniel Fagrey
 * 
 * @date April 16, 2018
 * 
 * @par Professor: 
 *         Professor Roger Schrader
 * 
 * @par Course: 
 *         CSC 215- M002 - 1:00 pm
 * 
 * @par Location: 
 *         McLaury - 313
 *
 * @section program_section Program Information 
 * 
 * @details This program attempts to find a solution for a knight on a 
 *          chessboard. A solution is when the knight has made it to every 
 *          square on the board in one tour. Only the first solution will be
 *          found. 
 *
 *          The user has the choice to give, on the command line, a file that 
 *          provides the size of a chessboard and the starting position for
 *          the knight. If the user does not give a file, then a menu is 
 *          presented that will allow the user to give the size of the 
 *          chessboard (must be greater than 3) and the starting position 
 *          for the knight. The user will be continually prompted until they
 *          select the option to solve the tour. 
 *
 *          When the user selects the solve option. A 2D array is created that
 *          corresponds to those dimensions given by the user. However, the 
 *          board is created with extra rows and columns to allow the program
 *          to know when it "steps" off the board given by the user. The 
 *          the size of the board given by the user is filled with 0's in the 
 *          2D array and the outside is filled with -1's to mark where the
 *          board ends. The program then uses recursion to solve the Tour by 
 *          trying every possible combination for the knight until a solution 
 *          is found. 
 *
 * @section compile_section Compiling and Usage          
 *
 * @par Compiling Instructions: 
 *      No special compiling instructions
 * 
 * @par Usage: In order to use this program you must specify on the command 
               line the one file that you would the program to get input 
               into. 
      
   @verbatim  
   C:\Users\7416949\source\repos\csc215s18programs\prog3\prog3/sln
  
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  ------------------------------------------------------------- 
   <a href="https://gitlab.mcs.sdsmt.edu/7416949/csc215s18programs/commits/master">
   @endverbatim
 *
 ****************************************************************************/
#include<iostream>
#include<fstream>
#include<ostream>
#include "menu.h"
#include<cmath>
using namespace std;

int **createBoard( int size );

void printSolution(int **board, int size, int row, int col,
    int numTours, ostream &out );

void solveTour( int **board, int size, int rowPos, int colPos, int &used, int
    orignRow, int orignCol, int &numTours, int startingRow, int startingCol, 
    ostream &out );

bool readFromFile( ifstream &fin );

void freeUpBoard( int **board, int size );


/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function checks to make sure that a valid amount of command arguments 
 * are entered, calls funtions to read in from a file, calls functions to print
 * the menu, and calls functions to solve the tour. It will also print a 
 * message if there is no solution to the tour
 * 
 * @param[in]     argc - number of arguments on the command line
 * @param[in]     argv - contains the arguments entered on the command line
 * 
 * @returns 0 program ran successful.
 * @returns -1 unable to allocate memory for 2D array or failed to open files 
 *
 ****************************************************************************/
int main( int argc, char **argv )
{
    menu myMenu;

    ifstream fin;
    ofstream fout;

    string fileName;
    
    int rowPos = 7; 
    int colPos = 7;
    int size = 8;
    
    int **board;
    
    int used = 1;
    int numTours = 0;
    int choice = 0;

  
    //make sure the argument count is right
    if ( argc > 2 )
    {
        cout << "In order to use this program you must specify on the command "
            << "line the one file that you would the program to get input "
            " into. " << endl;
            
    }

    
    
    //start reading from the file
    if ( argc == 2 )
    {
        fileName = argv[1];

        fin.open( fileName );
    
        
        
        if (!fin.is_open())
        {
            cout << "Unble to open input file. " << endl;

            return -2;
        }
    
        
       
       //call read function
       if ( !readFromFile( fin ) )
           return -1;
    
        
       
       fin.close();

        return 0;
    }
    
    
    //if not a file, get the user choice for the menu option they would like
    do
    {
        setUpMainMenu( myMenu );

        choice = myMenu.getMenuSelection( true, rowPos, colPos, size );


        if ( choice == 1 )
            size = getSubMenu1(myMenu, rowPos, colPos);



        if ( choice == 2 )
            getSubMenu2(myMenu, rowPos, colPos, size);


    } while ( choice != 3 );


    
    //create board
    board = createBoard( size );


    
    //failed to allocate memory for board
    if (board == nullptr)
      return -1;

    
    //add 2 so the row and column get past the outer layer of -1's
    rowPos += 2;

    colPos += 2;

    
    board[rowPos][colPos] = 1;
   
   
    //solve tour
    solveTour( board, size, rowPos, colPos, used, rowPos, colPos,
        numTours, rowPos, colPos, cout );


  
   //tour was not successful 
   if ( numTours < 1 )
   {
      printSolution( board, size, rowPos, colPos, numTours, cout );
   }
    
   
   //free up board
   freeUpBoard( board, size );
   
   
   return 0;

}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function creates a 2D array simulating the size of the chessboard that 
 * the user wants. The array is made biggger than the size wanted by the user.
 * This larger part is filled with -1's and the part of the array that is the
 * same size as the wanted board is filled with 0's. This is so we know when we
 * go beyond the size of the board.
 * 
 * @param[in]     size - the size of the board that the user wants
 * 
 * @returns board a pointer to a 2D array that holds the board
 ****************************************************************************/
int **createBoard( int size )
{
   int **board;
   int i, j;

   
   //create new 2D array
   board = new ( nothrow ) int *[size + 4];

   
   
   //check for success
   if ( board == nullptr )
       return board;


  
   //dynamically allocate the array to hold the board. The board will be 
   //actually bigger than need be so we can tell when we step off it. 
   for ( i = 0; i < size + 4; ++i ) 
   {
       board[i] = new ( nothrow ) int [size + 4];
       
       
       
       if ( board == nullptr )
       {
          cout << "Memory allocation failure. " << endl;
           
          return board;
       }
   }

   
   
   //fill this array with negative ones
    for ( i = 0; i < size + 4; ++i )
    {
        for ( j = 0; j < size + 4; ++j )
        {
            board[i][j] = -1;
        }
    }

  

   
    
    //fill the part of the array the corresponds with the size entered by the 
    //user with zeros
    for ( i = 2; i < size + 2; ++i )
    {
        for ( j = 2; j < size + 2; ++j )
        {
            board[i][j] = 0;
        }
    }


   
    return board;
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This functions prints the board to either the screen or to a file given by
 * the user. 
 * 
 * @param[in]      board - a pointer to a 2D array that holds the board
 * @param[in]      size - the size of the board
 * @param[in]      row - the orignal starting row for the knight
 * @param[in]      col - original starting col for the knight
 * @param[in]      numTours - the number of tours that we have done
 * @param[in,out]  out - ostream that allows us to print either to file or to
 *                       screen
 *
 ****************************************************************************/
void printSolution( int **board, int size, int row, int col,
    int numTours, ostream &out )
{

    int i, j;

    //if no tour was found
    if (numTours == 0)
    {
        out << "Tour: # " << numTours + 1 << endl << setw(7)
            << size << " X " << size << " starting (" << row - 2 << ", " << 
            col - 2 << ")" << endl << endl << 
            "      No solutions for this case. " << endl << endl;
    
        return;
    }
   
    //prints the number of the tour, the size of the board, and the starting
    //postions
    out << "Tour: # " << numTours << endl << setw(7)
        << size << " X " << size << " starting (" << row - 2 << ", " << col - 2
         << ")" << endl << endl;
    
    //print only the part that's the size given by the user
    for (i = 2; i < size + 2 ; ++i)
    {
        out << "      ";
        
        
        
        for (j = 2; j < size + 2 ; ++j)
        {
            
            if ( board[i][j] < 10 )
                out << " ";

            out << board[i][j] << "  ";
            
        }
    
       
        
        out << endl;
    }
    

   
    out << endl << endl;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function attempts to solve the tour using recursion. It trys every
 * possible permutation that a knight can take until it finds one in which the
 * knight has visited all spaces in a single tour. When a knight leaves a 
 * space, the variable used is utilized to mark that place visited. Used is 
 * increased by one, so the places marked corresponds to the path taken by the 
 * knight. A 0 means that a space is free to move to. A -1 means that the end 
 * the board has been reached. This function only finds the first solution, not
 * all of them. 
 *
 * @param[in]      board - a pointer to a 2D array that holds the board
 * @param[in]      size - the size of the board
 * @param[in]      rowPos - the row of the knight
 * @param[in]      colPos - column of the knight
 * @param[in]      used - keeps track of the spaces that the knight has gone to
 * @param[in]      orignRow - the row that the knight was on previously 
 * @param[in]      orignCol - the column that the knight was on previously 
 * @param[in,out]  numTours - the number of tours that we have done
 * @param[in]      startingRow - the original row that the knight started on
 * @param[in]      startingCol - the original column that the knight started on
 * @param[in,out]  out - ostream that allows print to screen or file
 *
 ****************************************************************************/
void solveTour( int **board, int size, int rowPos, int colPos, int &used, int
    orignRow, int orignCol, int &numTours, int startingRow, int startingCol, 
    ostream &out )
{
   
    int i = 0;

    // holds all the numbers that the rows and columns are to decrease and
    //increase to see if the knight can move to an empty spot. 
    int vals[20] = { -2, 1, -1, 2, 1, 2, 2, 1, 2, -1, 1, -2, -1, -2, -2, -1 };
    
   

    //found a solution
    if (used == ( size * size ) )
    {
       ++numTours;

       //print board
       printSolution( board, size, startingRow, startingCol, numTours, out );
       
       return;
    }


    //sets the original row to the row that we are on 
    orignRow = rowPos;

    //sets the original column to the column that we are on 
    orignCol = colPos;
    
    
    
    //continue to try all the possible moves that a knight can take
    while ( i < 18 )
    {
        //0 means that a spot is empty
        if ( board[rowPos][colPos] == 0 )
        {
            ++used;

            //mark as used
            board[rowPos][colPos] = used;

            //recursion call to do the same moves on the next spot
            solveTour(board, size, rowPos, colPos, used, orignRow, orignCol,
                numTours, startingRow, startingCol, out);
           
            
            
            //makes sure that we do not find all the other solutions
            if (used == (size * size) )
                return;
            

           
            //decrememt used when we come back from a call so we can try 
            //another path
            used -= 1;

        }


        
        //if the move failed, we set rows and columns pack to their original 
        //postion
        rowPos = orignRow;

        colPos = orignCol;

       
        //move rows and colimns to try the next move that a knight can take
        rowPos += vals[i];

        colPos += vals[i + 1];

        
        //incrememt by 2 as rows and columns come in sets of 2
        i += 2;
    }

    
    
    //fails to find an open spot: set row and cols to the previous ones and 
    //make that postion open by setting it equal to 0
    rowPos = orignRow;

    colPos = orignCol;

    board[rowPos][colPos] = 0;

    
    return;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function reads in the size of the chessboard and the starting positions
 * from a file, instead of being given them by a user. This function then
 * calls the solve tour function to solve these tours. It will output an 
 * message if it can not find a solution. 
 *
 * @param[in,out]      fin - file intput stream
 * 
 ****************************************************************************/    
bool readFromFile( ifstream &fin )
{
    ofstream fout;
    int size, row, col;
    int **board;
    int used = 1;
    int numTours = 0;
    int temp;
    int i = 0;
    int startingRow, startingCol;
    
   
    
    //open output
    fout.open( "Solutions.txt", ios::app );

    if ( !fout.is_open() )
    {
        cout << "Unable to open output file. " << endl;

        return false;
    }
    
   
    
    //read in the file
    while (fin >> size)
    {
        ++i;

        fin >> row >> col;

        //create board
        board = createBoard(size);

        //failed to allocate memory for board
        if (board == nullptr)
            return false;

        
        //this is to check to see if the solving tour was successful
        temp = numTours;

        row += 2;

        col += 2;

        board[row][col] = 1;


        //solve tour
        solveTour(board, size, row, col, used, row, col,
            numTours, row, col, fout);


        
        
        //if no change in numTours, then no solution was found
         if ( temp == numTours )
         {
             fout << "Tour: # " << numTours + ( i - numTours ) << endl << 
               setw(7) << size << " X " << size << " starting (" << row - 2 << 
                ", " << col - 2 << ")" << endl << endl << 
                "      No solutions for this case. " << endl << endl << endl;
         
             ++numTours;
         
         }

        
         //free up board
         freeUpBoard(board, size);

         //set used back for next tour
         used = 1;
    }
   
    fout.close();
    
    return true;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This simply frees up the dynamically allocated array that we used for board. 
 * 
 * @param[in]     board - pointer to a 2D array that holds our board
 * @param[in]     size -  size of the board
 *
 ****************************************************************************/
void freeUpBoard( int **board, int size )
{
   int i;

   if ( board == nullptr )
       return;
   
   
   //delete every row
   for ( i = 0; i < size + 4; ++i )
   {
      delete [] board[i];
   }

   
   //delete the pointer
   delete [] board;

}
