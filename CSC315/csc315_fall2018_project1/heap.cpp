/***************************************************************************//**
* @file
******************************************************************************/
#include "functions.h"
/***************************************************************************//**
* @author Robert Minick
* 
* @par Description: Call class destructor to free up memory back to system
*
******************************************************************************/
heap::~heap()
{

}

/***************************************************************************//**
* @author Robert Minick
*
* @par Description: Call for the constructor to create the heap list class
*
******************************************************************************/
heap::heap()
{
  headptr = tailptr = nullptr;
}

/***************************************************************************//**
* @author Robert Minick
*
* @par Description: 
* This function is for test purposes to print out the current linked list
*
* @param [in]	size	variable holding current size of linked list heap
*
******************************************************************************/
void heap::printHuffHeap(int &size)
{
   huffNode* cur;
   
   cur = headptr;
   while(cur != tailptr)
   {
      cout << "Char: " << cur->ch << "\t\t" << "Frequency: " << cur->freq;
      cout << endl;
      cur = cur->next;
   };
}


/***************************************************************************//**
* @author Robert Minick
*
* @par Description: 
* This function creates a sorted linked list from the two arrays, and inputs
* information from the arrays into a struct and then inserts the node into
* the list
*
* @param [in]	chArr[]		Array holding ASCII character from input file
* @param [in]	freqArr[]	Array holding int value of frequence of ASCII
* @param [in]	numBytes	variable holding # of bytes from input file
* @param [in]   size		variable holding current size of linked list
* @return	true		heap created successfully
* @return	false		heap created unsuccessfully
******************************************************************************/
bool heap::makeMinHeap ( char chArr[], int freqArr[], int &numBytes, int &size)
{
   int i;
   int freq;
   char ch;

   for (i=0; i < SIZE; i++)
   {

      if(freqArr[i] > 0)
      {
         
         freq = freqArr[i];
         ch = chArr[i];
         //cout << ch << "\t" << freq << endl;
         makeHuffNodes( freq ,ch, size );
      }
   }
   return true;
}


/***************************************************************************//**
* @author Robert Minick
*
* @par Description:
* This function creates the actual Node for the hufftree linked list
*
* @param [in]	numTimes	variable holding frequency of ASCII char in list
* @param [in]	asci		variable holding actual ascii char
* @param [in]	size		variable holding current size of list
* return	false		returns false if node not created
* return	true		returns true if node creation successful
******************************************************************************/
bool heap::makeHuffNodes( int numTimes, char asci, int &size )
{
   huffNode* cur;
   huffNode* prev;

   // node allocation, error check and fill node
   huffNode *temp = new(nothrow) huffNode;

   // setting node as a leafnode
   temp->leftchild = nullptr;
   temp->rightchild = nullptr;
   
   // error check for node creation          
   if (temp == nullptr)
      return false;
   else
   {
      temp -> freq = numTimes;
      temp -> ch = asci;
   }

   // handle empty list
   if (headptr == tailptr)
   {
      //cout << "Enter first node to Handle empty list" << endl;
      temp -> next = tailptr;
      headptr = temp;
      size = 1;
      return true;
   }

   // handle insert with 1 node in list
   cur = headptr;
   prev = headptr;

   if(size == 1)
   {
      //cout <<"temp->freq= " << temp->freq << endl;
      //cout <<"cur->feq= " << cur->freq << endl;
      // enter 2nd node front of list
      if (temp->freq <= cur->freq )
      {
         //cout <<"Enter 2nd node front of list" << endl;
         temp -> next = cur;
         headptr = temp;
         size++;
         return true;
      }

      else
      {
         // enter 2nd node position 2 in list
         //cout << "Enter 2nd node back of list" << endl;
         temp -> next = tailptr;
         cur -> next = temp;
         size++;
         return true;
      }
   }
   // insert 3rd node and beyond
   if( size > 1 )
   {
      //cout << "Enter Node: " << size << endl;
      // insert front of list
      if (temp->freq <= cur->freq)
      {
         temp -> next = cur;
         headptr = temp;
         size++;
         return true;
      }

      // traverse list
      while( cur != tailptr &&  temp->freq >= cur->freq )
      {
         prev = cur;
         cur = cur->next;
      };

      if ( cur == tailptr )  // insert end of list
      {
          temp -> next = cur;
          prev -> next = temp;
          size++;
          return true;
      }
      else if ( temp -> freq <= cur -> freq) // insert middle
      {
         temp -> next = cur;
         prev -> next = temp;
         size++;
         return true;
      }

   }
   return true;
}


/***************************************************************************//**
* @author Robert Minick
*
* @par Description: 
* This function is the compression function that takes the frequency of the 
* first 2 nodes in linked list and creates a new Node with frequency value of
* the two nodes and then places a pointer to lower freq node as left child and
* the larger freq node as the right child
*
* @param [in]	size	variable holding the current size of linked list
* return	false	not able to place node back into linked list
* return	true	node recreated and reinserted
*
******************************************************************************/

bool heap::makeHuffHeap(int &size)
{
   huffNode* cur;
   huffNode* prev;
   prev = cur = headptr;
   
   if(size > 1)
   {
      // allocate memory for internal node
      huffNode* internalNode =  new huffNode;
      
       
      // removing first node in list
      internalNode->leftchild = cur;
      cur=cur->next;
      headptr = cur;
      size--;
      internalNode->rightchild = cur;
      cur = cur->next;
      headptr = cur;
      prev = headptr;
      size--;
      internalNode->freq = internalNode->leftchild->freq + internalNode->rightchild->freq;
      // test print
      //cout <<"Freq of leftchild = "<< internalNode->leftchild->freq << endl;
      //cout <<"Freq of rightchild = " << internalNode->rightchild->freq << endl;
      //cout <<"InternalNode of freq = " << internalNode->freq << endl;
            
      //cout <<"freq of next node is: " << cur->freq << endl;      
      // reinsert internal node into heap list
      if(cur == tailptr) // list is empty
      {
         internalNode->next = tailptr;
         headptr = internalNode;
         size++;
         //cout <<"entered into empty list" << endl;
         return makeHuffHeap(size);
      } 
      //cout <<"is " << internalNode->freq << " <= " << cur->freq << endl;
      else if(internalNode->freq <= cur->freq) // insert front
      {
         internalNode->next = cur;
         headptr = internalNode;
         size++;
         //cout <<"reinsert front of list"<<endl;
         return makeHuffHeap(size);
      }
      else // insert middle/end of list
      {
         prev = cur = headptr;
         if(size == 1)
         {
            internalNode->next = tailptr;
            prev->next = internalNode;
            size++;
            //cout <<"insert at end of list" << endl;
            //cout <<"current size is "<< size << endl;
            return makeHuffHeap(size); 
         }
         else if(size == 0)
         {
            internalNode->next = tailptr;
            headptr = internalNode;
            size++;
            //cout <<"current size is " << size << endl;
            return makeHuffHeap(size);
         }
         do 
         {
            //cout <<"moving pointer" << endl;
            prev = cur;
            cur = cur->next;
            //cout <<"internalNode->freq is " << internalNode->freq << endl;
            //if(cur != tailptr)
            //   cout <<"cur->freq is " <<cur->freq << endl;
            //else
            //   cout <<"cur at tailptr " << endl;
         }
         while( cur->next != tailptr && internalNode->freq > cur->freq );
         //cout <<"Cur->freq is " << cur->freq << endl;
         //cout <<"internalNode->freq is " << internalNode->freq << endl;
                  
         if(internalNode->freq <= cur->freq && cur != tailptr ) // insert front of duplicate 
         {
            internalNode->next = cur;
            prev->next = internalNode;
            size++;
            //cout <<"insert between two nodes front side" << endl;
            //cout <<"current size is "<< size << endl;
            return makeHuffHeap(size);
         }
         else if(internalNode->freq > cur->freq && cur != tailptr) 
         {
            prev = cur;
            cur = cur->next;
            internalNode->next = cur;
            prev->next = internalNode;
            size++;
            //cout <<"insert between two nodes back side" << endl;
            //cout <<"current size is "<< size << endl;
            return makeHuffHeap(size);
         }
         else if(cur == tailptr) // insert into back of list
         {
            internalNode->next = tailptr;
            prev->next = internalNode;
            size++;
            //cout <<"insert at end of list" << endl;
            //cout <<"current size is "<< size << endl;
            if(size > 1)
               return makeHuffHeap(size);
         }             
      
      }
   }
   // should only have 1 node so print to check for testing
   cur = headptr;
   if(size == 1)
   {
       //cout <<"There is 1 node in Heap: "<< endl;
       //cout <<"with frequency: " << cur->freq << endl;
   }
   return true;
}


