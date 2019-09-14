/*************************************************************************//**
* @file
*
* @mainpage Program 1 - Disgruntled Employee
*
* @section course_section Course Information
*
* @author Nathaniel Fagrey
*
* @date Feb. 23, 2018
*
* @par Professor:
*         Roger Schrader
*
* @par Course:
*         CSC 215 - M002 -  1:00 pm
*
* @par Location:
*         McLaury Building - Room 313
*
* @section program_section Program Information
*
* @details This program envisions a scenario in which a former 
* employee of a company goes into the company's system and erases all
* file name extensions and image file dimensions. This program will attempt
* to restore all image files to their previous state. 
*
* The user enters directories that have the image files that they would 
* like to restore. These directories are given on the command
* line. The program goes through each given directory looking for files.
* Once an file is found, the program tests to see if it is an image file by
* opening up the file in binary, and testing to see if it is an GIF, BMP, PNG,
* or JPG image. If it is none of these image types, the program assumes that  
* the file is not an image file. 
*
* After determining what type of image file the image is, the program will go 
* through the file in binary looking for the height and width of the image.
* These dimensions reside in unique locations for different image types. After
* finding the dimensions, the program will re-name the image file with its 
* dimensions and with its image type extension. 
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      No special compiling instructions. 
*
* @par Usage:
  @verbatim
  c:\> C:\Users\7416949\source\repos\csc215s18programs\prog1\prog1.sln
  In order to use this program, you must enter the directories 
  (via command line) that contain the image files you would like to restore.
  @endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug warnings for cstring functions still appear even though NO_WARNINGS
*      was added. 
*
*@par Modifications and Development Timeline:
 @verbatim
 Date          Modification
 ------------  -------------------------------------------------------------
 <a href="https://gitlab.mcs.sdsmt.edu/7416949/csc215s18programs/commits/master">
 GitLab Commits.
 
 @endverbatim
*
****************************************************************************/
#define _CRT_SECURE_NO_WARNGINGS
#include<iostream>
#include"imageClassifier.h"
#include"imageDimensions.h"
#include"Utilities.h"
#include<cstring>
#include<fstream>
using namespace std;

/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* The main function calls four other function: one to get the current 
* directory, one to check argument count, one to change directory, and one to
* do a directory listing. The main function also ensures that all directories
* are processed.
* 
* @param[in]     argc - number of arguments on the command line 
* @param[in]     argv - stores the arguments on the command line 
*
* @returns 0 program ran successful.
* @returns -1 wrong number of arguments entered
*
****************************************************************************/
int main( int argc, char **argv ) 
{
    ifstream fin;
    int i = 0;
    char dirPath[_MAX_PATH + 1] = "";
    char startingDir[_MAX_PATH + 1] = "";
    bool success;
    
    
    
    //gets current directory and stores it to starting directory
    strcpy( startingDir, getCurrDir() );
    
    cout << "Starting directory is: " << startingDir << endl << endl;
    
    
    
    do
    {
        //check argument count
        success = checkArgc( argc );

        
        
        //end program if incorrect number of arguments
        if ( !success )
            return -1;

        
        
        //copy the directory in argv to a string 
        strcpy( dirPath, argv[i + 1] );

        //letting user know which directory is processing
        cout << endl << "Processing directory number " << i + 1
            << endl;
        
        //attempt to change directories
        success = changeDir( dirPath );

        
        
        if ( success )
        {
            //lists all sub-directories and files
            dirListing( fin );

            //changes directory to orinigal starting directory 
            changeDir( startingDir );
        }
        
        

        //makes sure that all directories are processed. 
        ++i;
    } while ( i < argc - 1 );

    return 0;
}
