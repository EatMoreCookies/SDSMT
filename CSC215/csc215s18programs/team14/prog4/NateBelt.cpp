/*************************************************************************//*
* @file contains the functions written by Nathaniel Fagrey
****************************************************************************/
#include<iostream>
#include<cstring>
#include"unsortedDouble.h"
#include"belt.h"
#include<iomanip>
#include<fstream>
#include<algorithm>

using namespace std;


/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function checks the command line arguments. The must be 3 command line
 * arguments: the program, the file to read in the boxes from, and the lenght
 * that every belt will be. This function makes sure that the value given for 
 * is a valid number. 
 * 
 * @param[in]      argCount - contains the number of arguments. 
 * @param[in]      beltLength - a character array that contains the length
 *
 * @returns true valid commandline arguments
 * @returns false invalid commandline arguments entered
 * 
 ****************************************************************************/
bool checkArguments( int argCount, char *beltLength )
{
    int i = 0;
    
   
    //check arguments
    if (argCount != 3)
    {
        cout << "Wrong number of arguments entered. In order to use this "
            << endl << "program, you must specify on the command line the "
            <<  endl << "program, your input file, and the length that you "
            << endl << "want each belt to be. " << endl;
            
            return false;
    }

    
    //while we havent reached the end of the c string
    while ( beltLength[i] != '\0' )
    {
       
        if ( !isdigit(beltLength[i]) )
        {
           cout << "Invalid belt length was entered. " << endl;

           return false;
           
        }

        ++i;
    }

    return true;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function checks to see if the amount of space that is taken up in the
 * belt is greater than the Length of belt. If it is, this function calls the 
 * remove function to get rid of the packages until there are no more in which
 * more than half of their width is hanging off the edge. If a box removed,
 * this function calls another function to print it to a file. 
 * 
 * @param[in,out]     out - ostream to print to file. 
 *
 ****************************************************************************/
void conveyorBelt::boxFalls( ostream &out )
{
    
    box package;
    
    //retrive first box that was put on. 
    retrieveFirst ( package );

    
    
    //while half the of the first box still hangs over 
    while ( space - theLength >= double( package.width ) / 2 ) 
    {
        space = space - package.width;

        //remove box
        if ( removeBox ( package ) )
            printToFile ( out, package, letter );
        
        retrieveFirst ( package );
    }
    
    
    return;

}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This prints to a file the box number that fell off the conveyor belt. It 
 * also prints the letter of the belt that it fell off. 
 * 
 * @param[int, out]   out - ostream to print to file
 * @param[in]         package - a box on our belt
 * @param[in]         conveyor - letter of the conveyor that the box falls off
 * 
 ****************************************************************************/
void printToFile( ostream &out, box package, char conveyor )
{
   conveyor = toupper( conveyor );

   out << setw(8) << "Box " << package.boxNumber << " has fallen off the " 
       "conveyor belt " << conveyor << endl;

}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function checks to see which conveyor belt the package can be added to.
 * This function also checks to see if the package can be rotated on the belt
 * in order to take up less space. 
 * contains the number of arguments. 
 *
 * @param[in,out]   package - a box on our conveyor belt   
 * @param[in,out]   A - conveyor belt A 
 * @param[in,out]   B - conveyor belt B
 * @param[in,out]   C - conveyor belt C
 *
 * @returns A box went on belt A
 * @returns B box went on belt B
 * @returns C box went on belt C
 * @returns Z box didnt go on any belt
 * 
 ****************************************************************************/
char addToBelt ( box &package, conveyorBelt &A, conveyorBelt &B, 
    conveyorBelt &C )
    
{
    
    if ( package.depth <= A.theWidth )
    {
        if ( package.width <= A.theWidth )
            
            //swap vals so we take up the least amount of space on the belt
            swap( package.width, package.depth ); 
          
        
        
        //add to the total length
        A.space += package.width;
        
        return 'A';
    }

    
    if ( package.depth <= B.theWidth )
    {
        if ( package.width <= B.theWidth)
            
            //swap vals so we take up the least amount of space on the belt
            swap( package.width, package.depth ); 
          
        
        //add to the total length
        B.space += package.width;
        
        return 'B';
    }


    if ( package.depth <= C.theWidth )
    {
        if ( package.width <= C.theWidth)
            
            //swap vals so we take up the least amount of space on the belt
            swap( package.width, package.depth ); 
          
        
        //add to the total length
        C.space += package.width;
        
        return 'C';
    }
   
    return 'Z';
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function retrieves the first item in our queue. 
 *
 * @param[in,out]   package - a box on our conveyor belt   
 *
 * @returns true able to retreive item
 * @returns false failed to retrieve item
 * 
 ****************************************************************************/
bool conveyorBelt::retrieveFirst (  box &package )
{
   return theBelt.retrieve( package, 1 );
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function adds the read in information of width, depth, and height into
 * a package, along with its box number
 *
 * @param[in,out]   package - a box on our conveyor belt   
 * @param[in]       width - width of the box
 * @param[in]       height - height of the box
 * @param[in]       depth - depth of the box
 * 
 ****************************************************************************/
void addToPackage ( box &package, int width, int height, int depth, 
    int boxNum )
{
    package.depth = depth;

    package.width = width;

    package.height = height;

    package.boxNumber = boxNum;

    return;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function prints the box simulation that we are on 
 *
 * @param[in,out]   out - an ostream object   
 * @param[in]       simNum - the number of the simulation that we are on
 * 
 ****************************************************************************/
void printSim ( ostream &out, int simNum )
{
    if ( simNum != 1)
        out << endl;
    
    out << "Simulation #" << simNum << ":" << endl;
}