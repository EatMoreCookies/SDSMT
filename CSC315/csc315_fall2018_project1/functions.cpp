/****************************************************************************//**
* @file   
********************************************************************************/

#include "functions.h"


/****************************************************************************//**
* @author:  Robert Minick
*
* @par description:
* This function checks the input/output file for an empty file and returns
* error message 
*
* @param [in]   fin     ifstream variable
* @param [in]	inFile	name of input file
* @return       true    file opened successfully
* @return       false   file did not open
*
*******************************************************************************/
bool chkemptyInFile(ifstream &fin, string inFile)
{
   int length;
   
   fin.clear();  

   fin.seekg(0, ios::end);
   length = fin.tellg();
   if (length == 0)
   {
      cout <<"Input file  is empty and cannot be processed" << endl;
      return true;
   }
   
   fin.clear();

   fin.seekg(0, ios::beg);

   return false;
}

