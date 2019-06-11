/****************************************************************************//**
* @file contain funtions made by Nate
********************************************************************************/
#include"functions.h"

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function reads in the characters from the file and puts them into two 
* arrays. One array contains the character, the other contains the frequncy at
* which that letter appears.   
*
* @param [in,out]  chArr - an array that contains the characters found
* @param [in,out]  freqArr -  contains the frequencies of characters.
* @param [in,out]  fin -  a file stream input object
* @param [in,out]  numWords - number of unique words
*
* returns  numBytes -  number of bytes read in the file
*
*******************************************************************************/
int readInHistogram ( char chArr[], int freqArr[], ifstream &fin, int &numWords )
{
        int numBytes = 0;

        char ch;
        
	//read entire file
	while (fin.read((char*) &ch, 1))
        {
                chArr[ch] = ch;

                if ( freqArr[ch] == 0 )
                        ++numWords;

                freqArr[ch] += 1;
                ++numBytes;

         }

       return numBytes;
}


/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function prints the histogram to the encoded file so we can access it 
* later for decoding.
*
* @param [in,out]  fout - ouput stream object
* @param [in,out]  freqArr -  contains the frequencies of characters.
* @param [in,out]  chArr - an array that contains the characters found
*
*******************************************************************************/
void readHistToFile (ofstream &fout, int freqArr[], char chArr[] )
{
     int bytesWriten = 0;

     fout.clear();

     fout.seekp(0, ios::beg);

     //this will later hold the size that we need to
     fout.write((char *) &bytesWriten, sizeof (int ));

     for (int i = 0; i < SIZE; ++i )
     {
            if (freqArr[i] != 0)
            {
                fout.write((char *) &chArr[i], 1 );
                fout.write((char *) &freqArr[i], sizeof(int) );
            }
     }
     
     //how many bytes we have written
     bytesWriten = fout.tellp();
     
     //seek back to the beginning 
     fout.seekp(0, ios::beg);
      
     //print the size
     fout.write((char *) &bytesWriten, sizeof (int ));

     fout.seekp(0, ios::end);
}

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function reads in the histogram from the encoding to it can use it 
* for decoding.  
* 
* @param [in,out]  fin -  a file stream input object
* @param [in,out]  freqArr -  contains the frequencies of characters.
* @param [in,out]  chArr - an array that contains the characters found
*
*******************************************************************************/
void readDecodeHist (ifstream &fin, int freqArr[], char chArr[] )
{
    int bytesRead;
    int i = 4;
    
    //read the number of bytes for the size of the histogram
    fin.read((char *) &bytesRead, sizeof(int));
   
    while ( i < bytesRead )
    {
        //read character
	fin.read((char *) &chArr[i], 1 );
      
        //read character frequency
	fin.read((char *) &freqArr[i], sizeof(int));
        
        i += 5;
    }
}
/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function just sets up the make huff table function   
*
* @param [in,out]  s1- stack of ints to hold the huff code
* @param [in,out]  arr -  an array structs that will hold our huff table
*
*******************************************************************************/
void heap::startHuffTable( stack<int> & s1, chCode arr[] )
{
   makeHuffTable( headptr, s1, arr );
}


/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function creates a table that will contain the character with the huffcode
* that it will get when we traverse the huff tree for that character. The table
* is composed of an array structs.
*
* @param [in,out]  node - huffnode that starts off pointing to the root of tree
* @param [in,out]  s1- stack of ints to hold the huff code
* @param [in,out]  arr -  an array structs that will hold our huff table
*
*******************************************************************************/
void heap::makeHuffTable (huffNode *node, stack<int> s1, chCode arr[]  )
{

     char ch;


     //we have reached the bottom of the tree
     if ( node->leftchild == nullptr && node->rightchild == nullptr )
     {
         ch = node->ch;
         
	 //add character to table
         arr[ch].ch = ch;

         
	 //put huffcode into table
         while ( !s1.empty() )
         { 
             //shift struct code
             arr[ch].code = arr[ch].code << 1;
             
	     //put the bits in to stack into the code in the table
             arr[ch].code |= s1.top();
             arr[ch].sizeOfCode++;
             s1.pop();

         }

         return;
     }
     
     
     else
     {
         //go to the left child
         s1.push(0);
         makeHuffTable ( node->leftchild, s1 , arr);

         s1.pop();

         //go to the right child
         s1.push(1);
         makeHuffTable ( node->rightchild, s1, arr);

         s1.pop();
     }
}

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function encodes the file by every time a charactet is encountered, the 
* huff table is accessed with that character and the character's code is printed
* in the place of that character.   
*
* @param [in,out]  arr - an array that contains the huff table
* @param [in,out]  fin -  a file stream input object
* @param [in,out]  fout - file stream output object
*
* returns  numBytes -  number of bytes printed in the file
*
*******************************************************************************/
int encodeFile ( chCode arr[], ifstream &fin, ofstream &fout )
{
    char ch;
    unsigned char  outCode;
    unsigned char tempCode;
    int tempSize;
    int bitCounter = 0;
    int bytesWriten = 0;
    int bit = 0;


    while ( fin.read( (char *) &ch, 1 ) )
    {
        //so we do not affect our code table
        tempCode = arr[ch].code;

        //so we dont change our table
        tempSize = arr[ch].sizeOfCode;


        while ( tempSize > 0 )
        {
            //put the code from tempCode to outCode
            bit = tempCode & 1;
            outCode =  outCode << 1;
            outCode |= bit;

            ++bitCounter;

            --tempSize;
            tempCode = tempCode >> 1;

            //if the code has an entire byte in it output to the file
            if ( bitCounter == 8 )
            {
                fout.write((char *) &outCode, 1 );

                ++bytesWriten;

                outCode = '\0';

                bitCounter = 0;
            }

        }

    }
    
    return bytesWriten;
}

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function just prints the size of the file that we will encode.   
*
* @param [in]  numBytes - number of bytes read in the file
* @param [in]  numWords - number of unique words
* @param [in]  fileName - name of file 
*
*******************************************************************************/
void printSize ( int numBytes, int numWords, char *fileName )
{
     cout << "Huffman Encoder Pass 1" << endl << "----------------------" << endl;


     cout << "Read " << numBytes << " bytes from " << fileName << ". Found " << numWords
            << " code words " << endl << endl;
}


/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function prints out our huff table. This includes the ACSII value of our
* charcter, the character, the probability of that character, and the huffcode 
* for that character. 
*
* @param [in,out]  freqArr -  contains the frequencies of characters.
* @param [in,out]  chArr - an array that contains the characters found
* @param [in,out]  prob -  contains the probabilites of characters.
* @param [in,out]  arr - an array of structs that contains our huff table
*
*******************************************************************************/
void printTable ( int freqArr[], char chArr[], double prob[],  chCode arr[] )
{
     unsigned char tempCode;
     
     //print header
     cout << "Huffman Code Table" << endl << "------------------" << endl;

     cout << "ASCII Code" <<"     " << "Probablilty (%) " << "    "
             << "Huffman Code" << endl;
     
     //go through table and histogram to print info
     for ( int i = 0; i < SIZE; ++i )
     {   
	if (freqArr[i] != 0 )
        {
             cout << arr[i].ch - 0 << " ("; 
             
             if ( arr[i].ch == 10 )
                 cout << "\\n";
             
	     else 
	      	cout << arr[i].ch;
	      
	     cout  << ") " << setw(16) << fixed << setprecision(2) << prob[i] * 100 << setw(16);

             //so we dont mess with the table
             tempCode = arr[i].code;
             
	     //print code
             for ( int j = 0; j < arr[i].sizeOfCode; ++j )
             {
                 int bit = tempCode & 1;
                 cout << bit;
                 tempCode = tempCode >> 1;
             }

             cout << endl;
        }
    }
}
/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function calculates the probability of each character. 
*
* @param [in,out]  freqArr - an array that contains the frequencies of our 
*                            characters
* @param [in]      numBytes -  number of bytes we have read from the file
* @param [in,out]  prob - probablilty of each character 
*
*******************************************************************************/
void calcProb ( int freqArr[], int numBytes, double prob[] )
{


  for (int i = 0; i < SIZE; ++i )
  {
       if ( freqArr[i] != 0 )
       {
           prob[i] = double(freqArr[i]) / numBytes;
       }
  }

}

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function calculates the entropy of the encoding
*
* @param [in,out]  prob - an array that contains the probability of each character
*
* returns  sum - the entropy
*
*******************************************************************************/
double calcEntropy ( double prob[] )
{
   double sum = 0;

   for (int i = 0; i < SIZE; ++i )
   {
       if ( prob[i] != 0 )
           sum += prob[i] * log2(prob[i]);

   }

   return -1 * sum;
}

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function prints the how the size of the file differs after encoding
*
* @param [in]  numBytes - number of bytes written to the file
* @param [in]  fileName - name of file
* @param [in]  size - size of histogram
*
*******************************************************************************/
void printPass2 ( int numBytes,  char *fileName, int size )
{
     cout << endl << "Huffman Coder Pass 2" << endl << "--------------------" << endl;
     cout << "Wrote " << numBytes << " bytes to " << fileName << " (" << size + numBytes
	     << " bytes including histogram) " << endl;

}

/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function calculates the average bit per symbol in the file   
*
* @param [in,out]  prob - probability of each character
* @param [in,out]  arr - huff table
*
* returns  sum - average bit per symbol
*
*******************************************************************************/
double  calcAvgBits ( double prob[], chCode arr[] )
{
    double sum = 0;

    for (int i = 0; i < SIZE; ++i )
    {
        if ( prob[i] != 0 )
                sum += prob[i] * arr[i].sizeOfCode;
    }

    return sum;
}


/****************************************************************************//**
* @author:  Nathaniel Fagrey
*
* @par description:
* This function prints all the statistics of our encoding; such as entropy, 
* average bits per symbol, original size, ect.   
*
* @param [in]     original - size of our original file
* @param [in]     compressed - size of our encoded file
* @param [in,out] prob - probability of each character
* @param [in,out] chCode 
* returns  numBytes -  number of bytes printed in the file
*
*******************************************************************************/
void printCodeStats ( int original, int compressed, double prob[], chCode arr[] )
{
     cout << endl << "Huffman Coding Statistics" << endl <<  "------------------------" << endl;

     cout << "Compression Ratio = " << double(compressed) / original * 100  << "%" << endl
          << "Entropy = " << calcEntropy (prob) << endl
          << "Average bits per symbol in the Huffman Coding = " << calcAvgBits( prob, arr ) << endl;

}

void printDecoder ( int bytesRead, int bytesWrite, char *inFile, char *outFile, int histSize )
{   

    cout << "Huffman Decoder" << endl << "--------------------" << endl;
    cout << "Read " << bytesRead - histSize << " encoded bytes from " << inFile << " (" << bytesRead
	    << " bytes including histogram) " << endl;
    cout << "Wrote " << bytesWrite << " decoded bytes to " << outFile << endl;
    cout << "Compression Ratio " << fixed << setprecision(2) 
	    <<  double(bytesRead - histSize ) /  bytesWrite * 100  << "%" << endl;
}



int heap::decodeFile ( istream &fin, ofstream &fout )
{
    unsigned char ch;
    char toPrint;
    int bitCounter = 0;
    int bit;
    int bytesWrote;
    huffNode *node = headptr;
    int direction;

    while (fin.read((char*) &ch, 1 ) )
    {
        bitCounter = 0;

        while ( bitCounter < 8 )
        {
            bit = ch & 128;
            if (bit == 128 )
                    direction = 1;
            else
                direction = 0;

            ch = ch << 1;

            cout << direction << endl;
            if ( findChars (node, direction, toPrint ) )
            {
                fout.write((char *) &toPrint, 1 );

                ++bytesWrote;

                node = headptr;
            }
            ++bitCounter;

        }

     }

     return bytesWrote;
}

bool heap::findChars (huffNode *&node, int direction, char &ch )
{
    //cout << "Made it to find chars " << endl;

    if (direction == 0 )
    {
        node = node->leftchild;

        if (node->leftchild == nullptr && node->rightchild == nullptr )
        {
             ch = node->ch;

             return true;

        }

       return false;

    }

    else
    {
        node = node->rightchild;

        if (node->leftchild == nullptr && node->rightchild == nullptr )
        {
             ch = node->ch;

             return true;

        }

        return false;

    }

}

