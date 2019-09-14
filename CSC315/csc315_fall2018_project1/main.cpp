/**************************************************************************//**
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
 * This program utilizes the Huffman coding techniques to compress the contents
 * of a file utilizing stack, a minHeap class, a and linked list to compress file
 * contents. The program will then output the compression heap to an output file
 * to decompress its contents and restore the input file to its original data
 * set.  
 *  1) We will read in the contents of a file in binary, one byte at a time.
 *  2) Create a histogram using two arrays, one to track the unique character
 *     and a seperate array of same size to track the frequency of each character
 *  3) Function call to create a minHeap linked list of structs containing the
 *     unique character and its frequency count within the input file for future
 *     compression.
 *  4) Create a Huffman tree of minHeaps and creating an internal node of frequency
 *     of the two minNode frequencies added together, where the smallest heapNode
 *     becomes the leftchild leafNode and the other, the right child leafNode. The
 *     new internal node will be put back into the minHeap and the process will be
 *     repeated untile the Huffman tree contains just a single node.
 *   
 *  5). From the tree, create a table that stores the characters and their respective
 *      codes. 
 *
 *  6). Using this table, create a new encoded file from the original. 
 *
 *  7). For the decode, the histogram of the original is stored in the encoded file.
 *      So, read in the, histogram and re-make the tree to do the decode.
 *
 *  8). Deocode the file by following the bit streams in the tree until a character is
 *      found.
 *
 *  9) Out put characters to a new file, it should be the same as the original. 
 *
 *
 *
 * @par Bug List
 *	Insert here what is not working
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  -------------------------------------------------------------
   <a href="git@gitlab.mcs.sdsmt.edu:7416949/csc315_fall2018_project1.git">
   @endverbatim
 *
 ****************************************************************************/


#include "functions.h"


/****************************************************************************//**
* @author:  Nathaniel Fagrey, Robert Minick
*
* @par description:
* Main serves basically as a place to pass functions. It does open the files and
* check for success though.
*
* @param [in]      argc - number of arguments
* @param [in,out]  argv - contains arguments
*
* returns  0 - program successful
* returns -1 - empty input file was given
*
*******************************************************************************/
int main(int argc, char *argv[])
{
   // Variable declaration
   bool status;
   int size = 0;
   char chArr[SIZE] = { "" };
   int intArr[SIZE] = { 0 };

   ifstream fin;
   ofstream fout;
  
   int numBytes, fileSize;
   
   double prob[SIZE] = {0};

   heap myHeap;
   stack<int> s1;

   chCode arr[SIZE];
   
   int numWords = 0;
   int bytesWritten = 0;
   int histSize = 0;

 




   // Check commandline arguments
   if(argc !=4)
   {
      cout << "This program requires exactly 4 input parameters, ";
      cout << "and " << argc << " parameters were entered" << endl;
      cout << "Please check parameters and recompile.  Program exiting" << endl;
      return -1;
   }

   
   //make sure second argument valid
   if ( (strcmp(argv[1], "-e") != 0 ) && ( strcmp (argv[1], "-d") != 0 ) )
   {
      cout <<"This program requires an encoding parameter of '-e'" << endl;
      cout <<"or a decoding parameter of '-d' " << endl;
      cout <<"Parameter sent is: " << argv[1] << " Program exiting" << endl;
      fin.close();
      fout.close();
      exit(-1);
   }
   
   fin.open( argv[2] );

   if (!fin)
   {
      cout << "Failed to open input file..." << endl;
      exit(1);
   }
   
   
   fout.open( argv[3] );
   
   if (!fout)
   {
      cout << "Failed to open output file..." << endl;
      exit(1);
   }
   
   
   if (chkemptyInFile(fin, argv[2]))
   {
         return -1;
   }
  
   if ( strcmp(argv[1], "-e" ) == 0 )
   {
	//read in histogram
        numBytes = readInHistogram ( chArr, intArr, fin, numWords );
        
	//print size of file
        printSize (numBytes, numWords, argv[2] );
        
	//print histogram to file
        readHistToFile (fout, intArr, chArr );

        histSize = fout.tellp();
        

	//make heap, tree, and table
        myHeap.makeMinHeap (chArr, intArr, numBytes, size );

        myHeap.makeHuffHeap ( size );

        myHeap.startHuffTable (s1, arr );


        calcProb( intArr, numBytes, prob );
       
	
	//print table
        printTable (intArr, chArr, prob, arr );

        fin.clear();

        fin.seekg(0, ios::beg);
        
	//encode file
        bytesWritten = encodeFile(arr, fin, fout);
        
	//print statistics
        printPass2 (bytesWritten, argv[3], histSize );

        printCodeStats (numBytes, bytesWritten, prob, arr );
      
   }
   
   else if ( strcmp(argv[1], "-d") == 0 )
   {
      
      //decode histogram
      readDecodeHist (fin, intArr, chArr );

      histSize = fin.tellg();

      //make heap, tree, and table
      myHeap.makeMinHeap (chArr, intArr, numBytes, size );

      myHeap.makeHuffHeap ( size );

      myHeap.startHuffTable (s1, arr );
   
      //decode file
      myHeap.decodeFile(fin, fout );

      numBytes = fout.tellp();

      fin.clear();

      fin.seekg(0, ios::end);

      fileSize = fin.tellg();
          
      //print decoder
      printDecoder(fileSize, numBytes, argv[2], argv[3], histSize );
  }   
   
   
   //close files

   fin.close();
   fout.close();   
   
   return 0;
}

