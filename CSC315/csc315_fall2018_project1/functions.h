/***************************************************************************//**
* @file
******************************************************************************/
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include<stack>
using namespace std;


static const int SIZE = 256;




/***************************************************************************//**
* STRUCTURES
****************************************************************************/

/*!*@brief struct to hold huffTable*/
struct chCode
{
   char ch;			/*!< variable character string*/
   unsigned char code = '\0';   /*!< variable initialization*/
   int sizeOfCode = 0;          /*!< variable for size of file*/
};

/*!*@brief class to hold heap linked list*/
class heap
{
   private:
      /*!*@brief struct of pointers to left and right children*/
      struct huffNode
      {
         int freq;              /*!< multiple character counter*/
         char ch;               /*!< ascii representation character*/
         huffNode *next;        /*!< address to next node*/
         huffNode *leftchild;   /*!< address to left child huffNode*/
         huffNode *rightchild;  /*!< address to right child huffNode*/

      };
      huffNode *headptr;        /*!< address to head node of list*/
      huffNode *tailptr;        /*!< address to tail node of list*/
  
    public:
      heap();
      ~heap();
      
      // class function protocols
      bool makeHuffNodes( int numTimes, char asci, int &size );//!< a member function. 
      bool makeHuffHeap(int &size);//!< a member function.
      void printHuffHeap(int &size);//!< a member function.
      bool makeMinHeap( char chArr[], int freqArr[], int &numBytes, int &size);//!< a member function.
      void makeHuffTable (huffNode *node, stack<int> s1, chCode arr[]  );//!< a member function.
      void startHuffTable ( stack<int> &s1, chCode arr[] );//!< a member function.
      void decodeFile ( istream &fin, ofstream &fout);//!< a member function.
      bool findChars (huffNode *&node, int direction, char &ch );//!< a member function.
};

/***************************************************************************//**
* FUNCTION PROTOTYPES
******************************************************************************/
void printSize ( int numBytes, int numWords, char *fileName );
int readInHistogram ( char chArr[], int freqArr[], ifstream &fin, int &numWords );
int encodeFile ( chCode arr[], ifstream &fin, ofstream &fout );
bool chkemptyInFile(ifstream &fin, string inFile);
void printDecoder ( int bytesRead, int bytesWrite, char *inFile, char *outFile, int histSize );
double  calcAvgBits ( double prob[], chCode arr[] );
void printCodeStats ( int original, int compressed, double prob[], chCode arr[] );
void calcProb ( int freqArr[], int numBytes, double prob[] );
double  calcEntropy (double prob[]);
void printTable ( int freqArr[], char chArr[], double prob[],  chCode arr[] );
void printPass2 ( int numBytes, char *fileName, int histSize );
void readHistToFile (ofstream &fout, int freqArr[], char chArr[] );
void readDecodeHist (ifstream &fin,  int freqArr[], char chArr[] );


#endif // !_FUNCTIONS_H

