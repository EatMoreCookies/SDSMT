/******************************************************************************
 * Name: Fagrey, Nathaniel 
 * ID: 7416949
 * Section: M0002
 * Homework 12
 *****************************************************************************/


#include "unsortedDouble.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;





bool unsortedDouble::isEmpty()
{
    if (headptr == nullptr || tailptr == nullptr )
        return true;

    
    return false;
}




int unsortedDouble::size()
{
    int size = 0;
    node *temp = headptr;

    while ( temp != nullptr )
    {
        temp = temp->next;
        ++size;

    }

    return size;

}

bool unsortedDouble::push_back( string val )
{
    node *curr = headptr;
    node *temp = headptr;

    temp = new (nothrow ) node;
    
    if ( temp == nullptr )
        return false;

    //inserting into empty list
    if ( headptr == nullptr )
    {
        headptr = temp;

        tailptr = temp;

        temp->item = val;

        temp->next = nullptr;

        temp->last = nullptr;
    
        return true;
    }

    curr = tailptr;
    
    tailptr = temp;

    temp->next = nullptr;

    curr->next = temp;

    temp->last = curr;

    temp->item = val;

    return true;

}

bool unsortedDouble::push_front(string val)
{
    node *curr = headptr;
    node *temp = headptr;

    temp = new (nothrow ) node;
    
    if ( temp == nullptr )
        return false;

    //inserting into empty list
    if ( headptr == nullptr )
    {
        headptr = temp;

        tailptr = temp;

        temp->item = val;

        temp->next = nullptr;

        temp->last = nullptr;
    
        return true;
    }

    headptr = temp;

    curr->last = temp;

    temp->next = curr;

    temp->item = val;

    temp->last = nullptr;

    return true;
}

bool unsortedDouble::pop_back(string &val)
{
    node* curr = tailptr;


    if ( headptr == nullptr )
        return false;

    
    
    tailptr = curr->last;

    //in case there is only one node
    if ( headptr == curr )
    {
        headptr = curr->next;

        val = curr->item;
        
        delete curr;

        return true;
    }
    
    curr->last->next = nullptr;

    val = curr->item;

    delete curr;

    return true;
}

bool unsortedDouble::pop_front(string &val)
{
    node* curr = headptr;


    if ( headptr == nullptr )
        return false;

    
    
    headptr = curr->next;

    //in case there is only one node
    if ( tailptr == curr )
    {
        tailptr = curr->last;

        val = curr->item;
        
        delete curr;

        return true;
    }

    curr->next->last = nullptr;

    val = curr->item;

    delete curr;

    return true;

}



void unsortedDouble::swap( unsortedDouble &l )
{
   node* temp;

   temp = headptr;

   headptr = l.headptr;

   l.headptr = temp;

   temp = tailptr;

   tailptr = l.tailptr;

   l.tailptr = temp;

}