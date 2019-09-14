/*************************************************************************//*
* @file Contains some functions written by Matthew Reff
****************************************************************************/

#include "belt.h"
#include "unsortedDouble.h"

using namespace std;

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in,out] width - first dimension of box
 * @param[in,out] length - second dimension of box
 * @param[in,out] height - third dimension of box
 * @param[in,out] infile - filestream dimensions are pulled from
 *
 * @returns true - dimensions are not the invalid case
 * @returns false - dimensions are the invalid case
 ******************************************************************************/

bool getBoxDimensions( int &width, int &length, int &height, ifstream &infile )
{
    //pull dimensions from file
    infile >> width >> length >> height;
    //return whether invalid or not
    return !( width == -1 && length == -1 && height == -1 );
}

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in,out] beltA - length of beltA
 * @param[in,out] beltB - length of beltB
 * @param[in,out] beltC - length of beltC
 * @param[in,out] infile - file stream to pull dimensions from
 *
 * @returns true - belt lengths are not the invalid case
 * @returns false - belt lengths are the invalid case
 ******************************************************************************/

bool getConveyorDimensions( int &beltA, int &beltB, int &beltC, ifstream &infile )
{
    //pull dimensions from file
    infile >> beltA >> beltB >> beltC;
    //return whether invalid or not
    return !( beltA == 0 && beltB == 0 && beltC == 0 );
}

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in,out] infile - ifstream to be opened
 * @param[in] fileName - char array of inputfile's name
 ******************************************************************************/

void openInputFile( ifstream &infile, char fileName[] )
{
    //try to open the ifstream with given name
    infile.open( fileName );
    if ( !infile.is_open() )
    {
        //if not opened, tell the user and exit program
        cout << "Input file could not be opened, exiting...";
        exit( 1 );
    }
}

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in,out] outfile - ofstream to be opened
 * @param[in] fileName - char array of outputfile's name
 ******************************************************************************/

void openOutputFile( ofstream &outfile, string fileName )
{
    //try to open the ifstream with given name
    outfile.open( fileName );
    if ( !outfile.is_open() )
    {
        //if not opened, tell the user and exit program
        cout << "Output file could not be opened, exiting...";
        exit( 2 );
    }
}

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in] package - box object to be added to belt
 *
 * @returns true - box was added to belt successfully
 * @returns false - box was not added
 ******************************************************************************/

bool conveyorBelt::addBox( box  &package )
{
    //add to private linked list, return if added or not
    return theBelt.push_back( package );
}

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in,out] package - box object to be added to belt
 *
 * @returns true - box was removed from belt successfully
 * @returns false - box was not removed
 ******************************************************************************/

bool conveyorBelt::removeBox( box &package )
{
    //pop off linked list and change package passed in into the box popped
    //from list, return if this was successful
    return theBelt.pop_front( package );
}

/***************************************************************************//**
 * @author Matthew Reff
 *
 *
 * @param[in,out] package - box object
 *
 * @returns true - every value in struct is equal
 * @returns false - at least one value is not equal
 ******************************************************************************/

bool box::operator==( box &package )
{
    //check all values in struct against eachother, return equal if all are same
    return ( width == package.width &&
        height == package.height &&
        depth == package.depth &&
        boxNumber == package.boxNumber );
        
}