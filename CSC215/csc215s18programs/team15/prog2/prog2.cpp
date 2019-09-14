/*************************************************************************//**
 * @file 
 *
 * @mainpage  Program 2 - The SRT Editor
 * 
 * @section course_section Course Information 
 *
 * @author Nathaniel Fagrey, Joseph Howell, Robert Parsons
 * 
 * @date   March 26, 2018
 * 
 * @par Professor: 
 *         Professor Roger Schrader
 * 
 * @par Course: 
 *         CSC 215 - M002 - 1:00 pm
 * 
 * @par Location: 
 *         McLaury Room 313
 *
 * @section program_section Program Information 
 * 
 * @details This program edits SRT files that are given by the user. An SRT
 *          file is a file that holds the subtitles for a movie. The user 
 *          enters the name of an SRT file on the command line. If the file 
 *          exists, the program attempts to read the contents of the file
 *          into a linked list before printing an option menu. If the SRT file
 *          does not exist, the menu will be displayed instead of trying to 
 *          read in the file first.
 *          
 *          The menu has 7 options: add a frame, remove a frame, retrieve a 
 *          frame, update a frame, print subtitles to screen, print range of 
 *          subtitles, and exit. The menu will continue to print until the user
 *          enters a valid option. 
 *
 *          All of these options, use a standard traversal of a linked list in
 *          order to do their tasks. Most of these functions return a true or
 *          false as to whether or not the operation was successful. After any
 *          option is selected and tried, the menu will continue to be printed.
 *    
 *          If the user selects the exit option, a sub menu will be printed 
 *          that asks the user if they want to save their changes or not. If   
 *          they select to save them, the program will write these updated   
 *          frames over the top of the frames in the original file. If the user 
 *          does not wish to save them, the program will just exit. 
 *
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      No special compiling instructions. 
 * 
 * @par Usage: 
        In order to use this program, you must specify,
        on the command line, the one SRT file that you would like
        to edit. 
   
   @verbatim  
    C:\Users\7416949\source\repos\team15\prog2\prog2.sln
   @endverbatim 
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  ------------------------------------------------------------- 
   <a href="https://gitlab.mcs.sdsmt.edu/csc215s18prog2/team15/commits/master">
   @endverbatim
 *
 ****************************************************************************/
#include"menu.h"
#include"srt.h"





/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function mainly serves as a place to call other functions. It also 
 * makes sure that the menu is continually printed until the user selects to 
 * exit. 
 * 
 * @param[in]      argc - number of arguments on the commmand line
 * @param[in]      argv - contains the arguments that were entered on the 
 *                        command line.
 * 
 * @returns 0 program ran successful.
 * @returns -1 user failed to enter the right information on the commmand line 
 *
 ****************************************************************************/
int main(int argc, char **argv) 
{
    ifstream fin;
    ofstream fout;

    string srtFile;

    menu mainMenu;
    srtList linkedList;

    int choice;
    bool val = true;


    
    //check argument count
    if ( !checkArgcVal( argc ) )
        return -1;


    
    srtFile = argv[1];

    //open file
    fin.open( srtFile );


    //if file exists read into it 
    if ( fin.is_open() )
    {
        readInList( fin, linkedList );
    }

    fin.close();
    
    
    
    //continue to print menu and get user options until 7 is selected
    do
    {   
        setUpMainMenu( mainMenu );

        cout << "Number of frames: " << linkedList.size() << endl;

        choice = mainMenu.getMenuSelection( val );

        GetFunctions( choice, linkedList, srtFile, fout );

        cout << endl;
    
    } while ( choice != 7 );
    
    
    
    return 0;
}


