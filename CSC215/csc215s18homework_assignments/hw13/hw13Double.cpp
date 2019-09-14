/******************************************************************************
 * Name: Fagrey, Nathaniel 
 * ID: 7416949
 * Section: M0002
 * Homework 13
 *****************************************************************************/
#include "unsortedDouble.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;

//forward retrieve
int unsortedDouble::retrieve( string val )
{
    node *temp = headptr;
    int i = 1;
    
    
    if ( headptr == nullptr )
        return false;
    



    while ( temp != nullptr )
    {
        
        if ( temp->item == val )
            return i;
        
        temp = temp->next;

        ++i;
    }


    return false;
}

int unsortedDouble::rretrieve( string val )
{
    node *temp = tailptr;
    int i = size();
    
    
    
    if (tailptr == nullptr)
        return false;

    
    while ( temp != nullptr ) 
    {
        if ( temp->item == val )
            return i;

        temp = temp->last;

        --i;
    }


    return false;
}

bool unsortedDouble::retrieve( string &item, int position)
{
    node *temp = headptr;
    int i = 1;

    if ( headptr == nullptr )
        return false;


    while ( temp != nullptr )
    {
        if ( i == position )
        {
           item = temp->item;

           return true;
        }
    
        temp = temp->next;

        ++i;
    }

    return false;
}

int unsortedDouble::countIf( function<bool(string)> cond )
{
    node *temp = headptr;
    int lengthCount = 0;

    if (headptr == nullptr)
        return false;
    
    while ( temp != nullptr )
    {
        if ( cond(temp->item) )
        {
            ++lengthCount;
        }

        temp = temp->next;
    }

    
    
    
    return lengthCount;
}