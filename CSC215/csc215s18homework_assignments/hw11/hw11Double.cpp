/******************************************************************************
 * Name: Fagrey, Nathaniel 
 * ID: 7416949
 * Section: M0002
 * Homework 11
 *****************************************************************************/
#include "unsortedDouble.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;

bool unsortedDouble::remove(int pos)
{
    node* curr;
    node* prev;
    node *temp;

    int i = 1;
    
    
    curr = headptr;

    if (headptr == nullptr || pos < 1)
        return false;
    
    
    //deleting from the front
    if (pos == 1)
    {
        headptr = curr->next;

        if (headptr != nullptr)
            curr->next->last = nullptr;

        else
            tailptr = headptr;


        delete curr;

        return true;
    }
       
        
        
    while (curr != tailptr && i != pos)
    {
        prev = curr;
        
        curr = curr->next;

        ++i;
    }

    //invalid 
    if (curr == tailptr && pos > i)
    {
        return false;
    }
    
    
    //back of list
    if (curr == tailptr && pos == i)
    {
        prev->next = nullptr;

        tailptr = prev;

        delete curr;
    
        return true;
    }

    prev->next = curr->next;

    curr->next->last = prev;

    delete curr;

    return true;
    
}

bool unsortedDouble::remove(string item)
{
    node *curr = headptr;
    node *prev = headptr;

    if (headptr == nullptr)
        return false;
    
   
    
    //front of the list 
    if (curr->item == item)
    {
        headptr = curr->next;

        if ( headptr != nullptr )
            curr->next->last = nullptr;

        else
            tailptr = headptr;

        delete curr;
        
        return true;
    }
    
    
    while (curr->item != item && curr != tailptr)
    {
        prev = curr;

        curr = curr->next;
    }

    if (curr == tailptr && curr->item != item)
      return false;
    
    //last item in list
    if (curr == tailptr && curr->item == item)
    {
        prev->next = nullptr;

        tailptr = prev;

        delete curr;

        return true;
    }

    
    prev->next = curr->next;

    curr->next->last = prev;

    delete curr;

    return true;

}
bool unsortedDouble::find(string val)
{
    node *curr = headptr;

    if(headptr == nullptr)
        return false;

    
    while (curr != tailptr && curr->item != val)
    {
        curr = curr->next;
    }

    if (curr == tailptr && curr->item != val)
        return false;

    
        return true;
}

bool unsortedDouble::rfind(string val)
{
    node *curr = tailptr;

    if(tailptr == nullptr)
        return false;

    
    while (curr != headptr && curr->item != val)
    {
        curr = curr->last;
    }

    if (curr == headptr && curr->item != val)
        return false;

    
        return true;
}