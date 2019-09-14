/*****************************************************************************//**
 * @file main.cpp
 * @mainpage Project 1: Huffman Coding
 *
 * @author Robert Minick
 * @author Nathaniel Fagrey
 *
 *
 * @par Class
 * Professor Dr. Larry Pyeatt
 * CSC315 Data Structures Sec. 02
 * Due Date: 10/19/2018
 *
 * @brief Program Description
 *
 * @par Todo List:
 *       1) Create Repository for Prog1                 Nate 10/4
 *       2) Open encoded binary file, read in           Rob 10/5
 *       3) Create histogram of symbols                 Nate 10/5
 *       4) Create Node class/struct                    Nate 10/5
 *       5) Create Tree functions
 *       6) Create Displayed functions
 *       7) Create Output file functions
 *       8) Create proper Makefile
 *       9) Create README.md file
 *      10) Meet Checkpoint 1 on Oct 8
 *      11) Meet Checkpoint 2 on Oct 15
 *      12) Doxygen
 *      13)
 *
 * @par Bug List
 *      Insert here what is not working
 *
 *****************************************************************************/

#include "functions.h"



class heap
{
   public:
      heap();
      ~heap();
      
      bool makeHuffNodes( int freq, char ch );
      void makeHuffHeap( ); 
      void printHuffHeap();
      bool makeMinHeap( char &chArr[], int &freqArr[], int &numBytes, int &size);
 
   private:
      struct huffNode
      {
         int freq; 		// multiple character counter 
         char ch; 		// ascii representation character 
         huffNode *next;	// address to next node
         huffNode *leftchild;   // address to left child huffNode
         huffNode *rightchild;  // address to right child huffNode

      };
      huffNode *headptr;	// address to head node of list
      huffNode *tailptr;	// address to tail node of list
      
};

void heap::printHuffHeap()
{
   huffNode* cur;
   
   cur = headptr;
   while(cur != tailptr)
   {
      cout << endl;
      cout << "Char: " << cur->ch << "\t\t" << "Frequency: " << cur->freq;
      cout << endl; 
   };
}

bool heap::makeMinHeap ( char &chArr[], int &freqArr[], int &numBytes, int &size)
{
   int i;
   int freq;
   char ch;   

   for (i=0; i < numBytes; i++)
   {
      if(freqArr[i] > 0)
      {
         freq = freqArr[i];
         ch = chArr[i];
         makeHuffNodes( numTimes, ASCII, size );
      }
   }
   return true;
}

void heap::makeHuffHeap(int &size)
{
   huffNode* cur;
   huffNode* prev;
   int tempfreq;   
   cur = headptr;
   
   if(size > 1)
   {   
      huffNode* internalNode new(nothrow) huffNode;
      internalNode->leftchild = cur;
      size--;
      cur = cur->next;   
      headptr = cur;

      internalNode->rightchild = cur;
      size--;
      cur = cur->next;
      headptr = cur;
      internalNode->freq = leftchild->freq + rightchild->freq;
      
      if(cur != tailptr) // list has at least 1 node
      {
         if(internalNode->freq < cur->freq) // insert front
         {
            internalNode = cur;
            internalNode->next = cur;
            headptr = internalNode;
            size++;
         }
         else // insert middle/end of list
         {
            while( cur != tailptr && internalNode->freq > cur->freq )
            {
               prev = cur;
               cur = cur->next;
            };
            
            if(cur == tailptr) // insert end of list
            {
               internalNode->next = cur;
               prev = internalNode;
               size++;
            }
            else // insert middle
            {
               internalNode = prev;
               internalNode->next = cur;
               prev->next = internalNode;
               size++;
            }
         }
      }
      else  // list is currently empty
      {
         internalNode = cur;
         headptr = internalNode;
         size++;         
      }
      if( size > 1)  // recursiive call to reduce huff tree to 1 node
         makeHuffHeap(size); 
   }
}

bool heap::makeHuffNodes( int numTimes, char &ASCII, int &size )
{   
   huffNode* cur;
   huffNode* prev;
        
   // node allocation, error check and fill node   
   huffNode *temp = new (nothrow) huffNode;
   if (temp == nullptr)
      return false;
   else
   {
      temp -> freq = numTimes;
      temp -> ch = ASCII;
   }
   
   // handle empty list
   if (headptr == tailptr)
   {
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
      // enter 2nd node front of list
      if (temp->freq < cur->freq )
      {
         temp -> next = cur;
         headptr = temp;
         size++;
         return true;
      }
      else 
      {
         // enter 2nd node position 2 in list
         temp -> next = tailptr;
         cur -> next = temp;
         size++;
         return true;
      }
   }   
   // insert 3rd node and beyond
   if( size > 1 )
   {
      // insert front of list
      if (temp->freq < cur->freq)
      {
         temp -> next = cur;
         headptr = temp;
         size++;
         return true;
      }
     
      // traverse list
      while( cur != tailptr &&  temp->freq > cur->freq )
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
      else if ( temp -> freq < cur -> freq) // insert middle
      {
         temp -> next = cur;
         prev -> next = temp;
         size++;
         return true;
      }

   }
   return true;  
}


void createHistogram (freq arr[] );

int main(int argc, char *argv[])
{
   // Variable declaration
   ifstream fin;
   ofstream fout;
   freq arr[256];
   vector<freq> histogram;
   heap huffTree;
   // Check commandline arguments
   if(argc !=4)
   {
      cout << "This program requires exactly 4 input parameters, ";
      cout << "and " << argc << " parameters were entered" << endl;
      cout << "Please check parameters and recompile.  Program exiting" << endl;
      return -1;
   }

   openInput_Binary(fin, argv[2]);
   // Insert function call to build histogram here
   createHistogram(arr);
   // Insert function call to build compression tree here
   
   openOutput_Binary(fout, argv[3]);
   // Insert function call to output decryption here

   fin.close();
   fout.close();
   return 0;
}

void makeheapNode ( struct *heapNode,  )
{
   heapNode* temp;
   heapNode** array;
        
   for ( int i = 0; i < 256; ++i )
   {
      temp = new(nothrow) heapNode;      
      
      arr[i].freq = 0;
      arr[i].ch = temp;
           
   }
}

/*
void readInHistogram ( freq arr[], ifstream &fin )
{
        char ch;

        while (fin.read((char*) &ch, 1)
        {
                arr[ch].ch = ch;
                arr[ch].numTimes += 1;
        }
}

void fillHistogram(ifstream &fin, freq arr[])
{
   char ch;
   int temp;
   
   while(fin.read((char*) &ch, 1)
   {
      temp = atoi(ch);
      arr[temp].ch = ch;
      arr[temp].numtimes += 1;
   }; 

}
*/



