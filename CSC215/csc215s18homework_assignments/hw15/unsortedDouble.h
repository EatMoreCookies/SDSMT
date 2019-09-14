#include <iostream>
#include <string>
#include <functional>

using namespace std;


#ifndef UNSORTEDDOUBLE__H
#define UNSORTEDDOUBLE__H


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
        
    private:
        struct node
        {
            YT item;
            node *next;
            node *last;
        };
        node *headptr;
        node *tailptr;
};
#endif



template<class YT>
unsortedDouble<YT>::unsortedDouble()
{
    headptr = NULL;
    tailptr = NULL;
}


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

template<class YT>
bool unsortedDouble<YT>::find(YT val)
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

template<class YT>
bool unsortedDouble<YT>::isEmpty()
{
    if (headptr == NULL && tailptr == NULL)
    {
        return true;
    }
    return false;
}

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


template<class YT>
bool unsortedDouble<YT>::push_back(YT val)
{
    int size = unsortedDouble::size() + 1;
    return unsortedDouble::insert(val, size);
}


template<class YT>
bool unsortedDouble<YT>::push_front(YT val)
{
    return unsortedDouble::insert(val, 1);
}


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