/*************************************************************************//*
* @file contians the linked list class and functions 
****************************************************************************/
#include <iostream>
#include <string>
#include <functional>
using std::nothrow;
using std::ostream;
using std::string;
using std::function;


#ifndef UNSORTEDDOUBLE__H
#define UNSORTEDDOUBLE__H

#ifdef UNSORTEDDOUBLE_EXPORTS
    #define UNSORTEDDOUBLE_API __declspec(dllexport)
#else
    #define UNSORTEDDOUBLE_API __declspec(dllimport)
#endif



/*! @brief this class holds a unsorted double linked list */
template <class YT>
class unsortedDouble
{
    public:
        unsortedDouble();

        // first change
        unsortedDouble (  const unsortedDouble<YT> &l ); 
        ~unsortedDouble();

        void clear();
        void print ( ostream &out, bool forward = true,
                     string seperator = ", " );
        bool insert ( YT val, int pos = 1 );
        bool remove ( int pos = 1 );

        // second change
        bool removeVal ( YT val );
        bool rfind ( YT val );
        bool find ( YT val );
        
        bool isEmpty( );
        int size();
        bool push_back ( YT val );
        bool push_front ( YT val );
        bool pop_back ( YT &val );
        bool pop_front ( YT &val );
        
        void swap ( unsortedDouble<YT> &l );
        int countIf ( function<bool ( YT ) > cond );
        int retrieve ( YT val );
        int rretrieve ( YT val );
        bool retrieve ( YT &item, int position );
    
    
    /** *******************************************************************
    * @struct  node unsortedDouble.h unsortedDouble.h
    *
    * @brief   A node structure used for the doubly linked list.
    *
    * @author  Schrader, Roger
    * @date    3/13/2018
    *********************************************************************/   
    private:
        struct node
        {
            YT item;        /*!< The item being stored*/
            node *next;     /*!< A Pointer to the next node. */
            node *last;        /*!< A Pointer to the previous node. */

        };              
                                            
            
        node *headptr;   /*!< A Pointer to the first item in the list */

        node *tailptr;   /*!< A Pointer to the last item in the list */
};

/*************************************************************************//**
 * @author Matthew Reff 
 * 
 * @par Description: 
 * Constructor for the unsorted doubly linked list. 
 * 
 ****************************************************************************/
template<class YT>
unsortedDouble<YT>::unsortedDouble()
{
    headptr = NULL;
    tailptr = NULL;
}

/*************************************************************************//**
 * @author Matthew Reff 
 * 
 * @par Description: 
 * Deconstructor for the unsortedDoubly linked list. 
 * 
 ****************************************************************************/
template<class YT>
unsortedDouble<YT>::~unsortedDouble()
{
    node * curr = headptr;
    while (headptr != NULL)
    {
        headptr = headptr->next;
        delete curr;
        curr = headptr;
    }
    tailptr = NULL;
}

/*************************************************************************//**
 * @author Matthew Reff 
 * 
 * @par Description: 
 * Deletes all nodes in the unsorted doubly linked list. 
 * 
 ****************************************************************************/
template<class YT>
void unsortedDouble<YT>::clear()
{
    node * curr = headptr;
    while (headptr != NULL)
    {
        headptr = headptr->next;
        delete curr;
        curr = headptr;
    }
    tailptr = NULL;
}

/*************************************************************************//**
 * @author Matthew Reff 
 * 
 * @par Description: 
 * Prints out the nodes from the beginning or the end of the list with a 
 *  character or string seperating the items that are printed out. 
 * 
 * @param[in,out]  out - ostream object
 * @param[in]      forward - if true print out forwards else print out
 *                           backwards
 * @param[in]      seperator - a string that seperates items that are printed
 * 
 ****************************************************************************/
template<class YT>
void unsortedDouble<YT>::print(ostream &out, bool forward,
    string seperator)
{
    if (forward)
    {
        node * temp = headptr;
        if (temp != NULL)
        {
            while (temp->next != NULL)
            {
                out << temp->item << seperator;
                temp = temp->next;
            }
            out << temp->item;
        }
    }
    if (!forward)
    {

        node * temp = tailptr;
        if (temp != NULL)
        {

            while (temp->last != NULL)
            {
                out << temp->item << seperator;
                temp = temp->last;
            }
            out << temp->item;
        }
    }
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function inserts a value into our list at a given position
 *
 * @param[in]      val - some item to be inserted
 * @param[in]      pos- position for val to inserted at
 * 
 * @returns true able to insert  
 * @returns false failed to insert 
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::insert( YT val, int pos)
{
    node * newNode = NULL;
    newNode = new(nothrow) node;
    node * curr = NULL;
    node * prev = NULL;
    int count = 2;
    int size;

    size = unsortedDouble::size();

    if (pos < 1 || pos > size + 1 || newNode == NULL)
    {
        return false;
    }

    newNode->item = val;

    if (isEmpty())
    {
        newNode->last = NULL;
        newNode->next = NULL;
        headptr = newNode;
        tailptr = newNode;
        return true;
    }

    if (pos == 1)
    {
        newNode->last = NULL;
        newNode->next = headptr;
        headptr->last = newNode;
        headptr = newNode;
        return true;
    }

    if (pos == (unsortedDouble::size() + 1))
    {
        newNode->last = tailptr;
        newNode->next = NULL;
        tailptr->next = newNode;
        tailptr = newNode;
        return true;
    }

    curr = headptr->next;
    prev = headptr;

    while (count != pos)
    {
        count++;
        prev = curr;
        curr = curr->next;
    }

    prev->next = newNode;
    curr->last = newNode;
    newNode->next = curr;
    newNode->last = prev;
    return true;
}
/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function a removes node from our list at a given position
 *
 * @param[in]      pos- position to remove 
 * 
 * @returns true able to remove  
 * @returns false failed to failed to remove
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::remove(int pos)
{
    int currentPos = 1;
    node * prev = NULL;
    node * curr = NULL;
    node * temp = NULL;
    if (pos < 1 || pos > unsortedDouble::size())
    {
        return false;
    }
    curr = headptr;
    prev = headptr;

    //removing last element
    if (unsortedDouble::size() == 1)
    {
        temp = headptr;
        delete temp;
        headptr = NULL;
        tailptr = NULL;
        return true;
    }

    //removing first
    if (pos == 1)
    {
        temp = headptr;
        headptr = headptr->next;
        headptr->last = NULL;
        delete temp;
        return true;
    }

    //end case
    if (pos == unsortedDouble::size())
    {
        temp = tailptr;
        tailptr = tailptr->last;
        tailptr->next = NULL;
        delete temp;
        return true;
    }

    //removing middle
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        currentPos++;
        if (pos == currentPos)
        {
            temp = curr;
            curr = curr->next;
            prev->next = curr;
            curr->last = prev;
            delete temp;
            return true;
        }

    }
    return false;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function looks for a specific value to remove. If it finds it, it 
 * it removes it. 
 *
 * @param[in]      val - some item to be removed
 * 
 * @returns true able to remove val 
 * @returns false failed to remove val 
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::removeVal(YT val)
{

    int currentPos = 1;
    int pos = -1;
    node * prev = NULL;
    node * curr = NULL;
    node * temp = NULL;

    if (unsortedDouble::size() == 0)
    {
        return false;
    }

    temp = headptr;
    while (temp != NULL)
    {
        if (temp->item == val)
        {
            pos = currentPos;
        }
        temp = temp->next;
        currentPos++;
    }
    if (pos == -1)
    {
        return false;
    }

    currentPos = 1;
    curr = headptr;
    prev = headptr;

    //removing last element
    if (unsortedDouble::size() == 1 && headptr->item == val)
    {
        temp = headptr;
        delete temp;
        headptr = NULL;
        tailptr = NULL;
        return true;
    }

    //removing first
    if (pos == 1)
    {
        temp = headptr;
        headptr = headptr->next;
        headptr->last = NULL;
        delete temp;
        return true;
    }

    //end case
    if (pos == unsortedDouble::size())
    {
        temp = tailptr;
        tailptr = tailptr->last;
        tailptr->next = NULL;
        delete temp;
        return true;
    }

    //removing middle
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        currentPos++;
        if (pos == currentPos)
        {
            temp = curr;
            curr = curr->next;
            prev->next = curr;
            curr->last = prev;
            delete temp;
            return true;
        }

    }
    return false;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function tries to find a value, starting from the end to the list
 *
 * @param[in]      val - some item to be found
 * 
 * @returns true able to find val
 * @returns false failed to find val
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::rfind(YT val)
{
    node * temp = NULL;
    temp = tailptr;
    while (temp != NULL)
    {
        if (temp->item == val)
        {
            return true;
        }
        temp = temp->last;
    }
    return false;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function tries to find a val, starting from the beginning of the list
 *
 * @param[in]      val - some item to be found
 * 
 * @returns true able to find val  
 * @returns false failed to find val
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::find( YT val )
{
    node * temp = NULL;
    temp = headptr;
    while (temp != NULL)
    {
        if (temp->item == val)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function checks to see if our list is empty 
 *
 * @returns true is empty 
 * @returns false is not empty 
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::isEmpty()
{
    if (headptr == NULL && tailptr == NULL)
    {
        return true;
    }
    return false;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function gets the size of our list and returns that number
 *
 * @returns size the size of our list
 * 
 ****************************************************************************/
template<class YT>
int unsortedDouble<YT>::size()
{
    int size = 0;
    node * temp = NULL;
    temp = headptr;
    while (temp != NULL)
    {
        size++;
        temp = temp->next;
    }
    return size;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function inserts a value into our list at a the very end of it
 *
 * @param[in]      val - some item to be inserted
 * 
 * @returns true able to insert  
 * @returns false failed to insert 
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::push_back(YT val)
{
    int size = unsortedDouble::size() + 1;
    return unsortedDouble::insert(val, size);
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function inserts a value into our list at the beginning of our list
 *
 * @param[in]      val - some item to be inserted
 *
 * @returns true able to insert  
 * @returns false failed to insert 
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::push_front(YT val)
{
    return unsortedDouble::insert(val, 1);
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function removes a value from the back of our list 
 *
 * @param[in,out]      val - the item that will contain the item we remove
 *
 * @returns true able to remove
 * @returns false failed to remove
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::pop_back(YT &val)
{
    int size = unsortedDouble::size();
    if (unsortedDouble::size() == 0)
    {
        return false;
    }
    val = tailptr->item;
    return unsortedDouble::removeVal(val);
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function removes a value from the front of our list 
 *
 * @param[in,out]      val - the item that will contain the item we remove
 *
 * @returns true able to remove
 * @returns false failed to remove
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::pop_front(YT &val)
{
    if (unsortedDouble::size() == 0)
    {
        return false;
    }
    val = headptr->item;
    return unsortedDouble::removeVal(val);
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function swaps the contents of our list with the contents of another
 * list
 *
 * @param[in,out]    l - a double linked list to be swapped
 * 
 ****************************************************************************/
template<class YT>
void unsortedDouble<YT>::swap(unsortedDouble &l)
{
    node * tempHead = NULL;
    node * tempTail = NULL;
    tempHead = headptr;
    tempTail = tailptr;
    headptr = l.headptr;
    tailptr = l.tailptr;
    l.headptr = tempHead;
    l.tailptr = tempTail;
}

/*************************************************************************//**
 * @author Nathaniel
 * 
 * @par Description: 
 * This function counts the number of items that pass a certain test in the
 * function that is passed in. 
 * 
 * @param[in]      cond - a function that sees if an item in our list passes
 *                        a certain test.
 *
 * @return  count  the number of items that meet the test
 * 
 ****************************************************************************/
template<class YT>
int unsortedDouble<YT>::countIf(function<bool(YT)> cond)
{
    int count = 0;
    node * temp = headptr;
    while (temp != NULL)
    {
        if (cond(temp->item))
        {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function finds a value ( starting at the beginning ) that is passed 
 * into it and returns the location of the value. 
 * 
 * @param[in]      val - an item to find in the list
 * 
 * @returns location the location of the item that we found
 * @returns 0 failed to find the item
 * 
 ****************************************************************************/
template<class YT>
int unsortedDouble<YT>::retrieve( YT val)
{
    int location = 1;
    node * temp = headptr;
    while (temp != NULL)
    {
        if (temp->item == val)
        {
            return location;
        }
        temp = temp->next;
        location++;
    }
    return 0;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function finds a value ( starting at the end ) that is passed 
 * into it and returns the location of the value. 
 * 
 * @param[in]      val - an item to find in the list
 * 
 * @returns location the location of the item that we found
 * @returns 0 failed to find the item
 * 
 ****************************************************************************/
template<class YT>
int unsortedDouble<YT>::rretrieve(YT val)
{
    int location = unsortedDouble::size();
    node * temp = tailptr;
    while (temp != NULL)
    {
        if (temp->item == val)
        {
            return location;
        }
        temp = temp->last;
        location--;
    }
    return 0;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This function gets an item at a certain position. 
 * 
 * @param[in,out]   item - will contain the item that we find
 * @param[in]       position - position of the item that we are going to get
 * 
 * @returns true found the item
 * @returns false failed to find the item 
 * 
 ****************************************************************************/
template<class YT>
bool unsortedDouble<YT>::retrieve(YT &item, int position)
{
    int currentPos = 1;
    node * temp = headptr;
    if (position < 1 || position > unsortedDouble::size())
    {
        return false;
    }
    while (temp != NULL)
    {
        if (currentPos == position)
        {
            item = temp->item;
            return true;
        }
        temp = temp->next;
        currentPos++;
    }
    return false;
}

/*************************************************************************//**
 * @author Matthew Reff
 * 
 * @par Description: 
 * This is the copy constructor for this class. It makes an exact copy of our 
 * list.
 * 
 * @param[in, out]    l - the list that we are copying
 * 
 ****************************************************************************/
template<class YT>
unsortedDouble<YT>::unsortedDouble(const unsortedDouble<YT> &l)
{
    headptr = NULL;
    tailptr = NULL;
    node * curr = l.headptr;
    node * prevCopy = NULL;
    if (const_cast<unsortedDouble&>(l).size() == 0)
    {
        return;
    }

    node * newNode = new(nothrow) node;
    newNode->next = NULL;
    newNode->last = NULL;
    newNode->item = curr->item;
    headptr = newNode;
    tailptr = newNode;
    prevCopy = newNode;

    if (const_cast<unsortedDouble&>(l).size() == 1)
    {
        return;
    }
    else
    {
        curr = curr->next;
    }

    while (curr != NULL)
    {
        node * newNode = new(nothrow) node;
        newNode->next = NULL;
        newNode->last = prevCopy;
        prevCopy->next = newNode;
        newNode->item = curr->item;
        tailptr = newNode;
        prevCopy = newNode;
        curr = curr->next;
    }
    return;
}



#endif
