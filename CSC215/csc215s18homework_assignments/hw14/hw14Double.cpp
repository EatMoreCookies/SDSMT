#include "unsortedDouble.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;

//hw 14
unsortedDouble::unsortedDouble(unsortedDouble &l)
{
    node * src;
    node * dest;
    node *temp;
    
    headptr = nullptr;
    tailptr = nullptr;

    if ( l.headptr == nullptr )
        return;

    headptr = new ( nothrow ) node;

    if ( l.headptr == nullptr )
        return;

    src = l.headptr;

    headptr->item = src->item;

    src = src->next;

    dest = headptr;

    headptr->last = nullptr;

    headptr->next = nullptr;

    tailptr = dest;
    
    while (src != nullptr)
    {
        temp = dest;
        
        dest = new ( nothrow ) node;

        if ( dest == nullptr )
            return;

        dest->item = src->item;

        dest->next = nullptr;

        dest->last = temp;

        temp->next = dest;

        tailptr = dest;

        src = src->next;

    }
}


//Hw 13
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

//Hw 12
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

//Hw 11
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

//Hw 10
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