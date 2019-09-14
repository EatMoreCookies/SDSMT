#include "unsortedDouble.h"
#include <iostream>
#include <string>
#include <functional>
using namespace std;

unsortedDouble::unsortedDouble()
{
    headptr = nullptr;
    tailptr = nullptr;
}

void unsortedDouble::clear()
{
    node *curr;
    
    curr = headptr;

    while (curr != nullptr)
    {
        headptr = curr->next;

        delete curr;
        
        curr = headptr;
    }
   
    tailptr = headptr; 
}

unsortedDouble::~unsortedDouble()
{
    clear();
}

bool unsortedDouble::insert(string val, int pos)
{
    node *curr;
    node *prev;
    node *temp;
   
    int i = 1;
    
    
    if (pos < 1)
        return false;
    
    
    temp = new ( nothrow ) node;
    {
        if ( temp == nullptr)
        {
            return false;
        }
    }
    
    
    //empty list
    if (headptr == nullptr || tailptr == nullptr)
    {
        if ( pos > 1)
            return false;
        
        temp->item = val;

        headptr = temp;

        tailptr = temp;

        temp->last = nullptr;

        temp->next = nullptr;

        return true;
    }


    curr = headptr;
    prev = headptr;
   
    //inserting into the front of the list
    if (pos == 1)
    {
        temp->next = headptr;

        temp->next->last = temp;
        
        temp->last = nullptr;
        
        headptr = temp;
       
        temp->item = val;
        
        return true;
    }
    
    
    while ( i != pos && curr != nullptr )
    {
        
        prev = curr;
       
        curr = curr->next;

        ++i;
    }

    
    if( curr == nullptr && pos > i )
        return false;
    
    //inserting into the end
    if (curr == nullptr )
    {
        temp->next = nullptr;

        prev->next = temp;

        temp->last = prev;

        tailptr = temp;

        temp->item = val;

        return true;
    }
    
    temp->last = prev;

    temp->next = prev->next;

    temp->item = val;

    curr->last = temp;

    prev->next = temp;

    return true;
}

void unsortedDouble::print( ostream &out, bool forward,
    string seperator)
{
    node *curr;
   
    if (forward)
    {
        curr = headptr;

        while ( curr != nullptr )    
        {   
            out << curr->item;
        
            curr = curr->next;

            if(curr != nullptr)
                out << seperator;
        } 
    }

    else 
    {
        curr = tailptr;

        while (curr != nullptr)
        {
            out << curr->item;

            curr = curr->last;

            if (curr != nullptr)
                out << seperator;
        }
    }
}