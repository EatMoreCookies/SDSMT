/*************************************************************************//*
* @file Holds the functions written by Benjamin Braun
****************************************************************************/

#include "belt.h"
#include <vector>
#include <algorithm>

using namespace std;

/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * sortBox takes a box structure and sorts the depth, height, and width so that
 * the depth is the smallest value, width is the next smallest value, and the
 * height is the largest value
 * 
 * @param[in,out]      ubox - the box structure to be sorted
 * 
 * 
 *****************************************************************************/

void sortBox( box &ubox )
{
    vector<int> box;
    
    // add dimensions to vector
    box.push_back( ubox.depth );
    box.push_back( ubox.height );
    box.push_back( ubox.width );

    // sort
    sort( box.begin(), box.end() );

    // depth smallest dimension
    ubox.depth = box[0];
    // width middle dimension
    ubox.width = box[1];
    // height largest dimension
    ubox.height = box[2];
}


/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * sortBelt takes three belts and sorts them based on their widths.
 * 
 * @param[in,out]      small - one of the conveyor belts to be sorted
 * @param[in,out]      medium - one of the conveyor belts to be sorted
 * @param[in,out]      large - one of the conveyor belts to be sorted
 * 
 *****************************************************************************/

void sortBelt( conveyorBelt &small, conveyorBelt &medium, conveyorBelt &large )
{
    vector<conveyorBelt> belt;

    // add belts to vector
    belt.push_back( small );
    belt.push_back( medium );
    belt.push_back( large );
    
    // sort using overloaded operator
    sort( belt.begin(), belt.end() );
    
    // smallest belt
    small = belt[0];
    // medium belt
    medium = belt[1];
    // largest belt
    large = belt[2];
    
}


/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * the constructor for the conveyor belt class. Sets theWidth, theLength and
 * space to 0.
 * 
 * 
 *****************************************************************************/

conveyorBelt::conveyorBelt()
{
    // initialize width, length and space on a belt
    theWidth = 0;
    theLength = 0;
    space = 0;
}


/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * deconstructor for the conveyorBelt class
 * 
 * 
 *****************************************************************************/

conveyorBelt::~conveyorBelt()
{
    // nothing necessary
}


/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * operator< overloads the < in order to compare two conveyorBelts. This
 * compares the widths of the two belts.
 * 
 * @param[in,out]      belt - the rhs belt structure to be compared to the lhs
 * 
 * @returns true - the lhs belt is less than the rhs belt
 * @returns false - the lhs belt is greater than or equal to the rhs belt
 *****************************************************************************/

bool conveyorBelt::operator<( conveyorBelt &belt )
{
    // sorts belts based on their width
    return ( theWidth < belt.theWidth );
}


/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * addtoConveyor takes a width, length and letter to set the conveyorBelt with
 * values
 * 
 * @param[in]      width - the width of the conveyorBelt
 * @param[in]      length - the length of the conveyorBelt
 * @param[in]      let - the letter of the conveyorBelt
 *
 * 
 *****************************************************************************/

void conveyorBelt::addtoConveyor( int width, int length, char let )
{
    // sets width, length and letter for a conveyor
    theWidth = width;
    theLength = length;
    letter = let;
}


/**************************************************************************//**
 * @author Benjamin Braun
 * 
 * @par Description: 
 * clearBelt clears the unsortedDouble of boxes from the conveyorBelt
 * 
 *****************************************************************************/

void conveyorBelt::clearBelt()
{
    // clears the unsortedDouble of boxes and resets the belts width and space
    theBelt.clear();
    space = 0;
    theWidth = 0;
}