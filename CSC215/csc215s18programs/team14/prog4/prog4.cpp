/***************************************************************************//**
 * @file 
 *
 * @brief Takes in belt lengths and package sizes from file, all packages
 * are placed on the smallest belt that can hld them, and packages that fall 
 * off the end are outputted to the console.
 *
 * @mainpage Program 4 - Conveyor Belts
 *
 * @section course_section Course Information
 *
 * @authors Nathaniel Fagrey, Benjamin Braun, Matthew Reff
 *
 * @date April 27, 2018
 *
 * @par Instructor:
 *         Dr. Schrader
 *
 * @par Course:
 *         CSC 215 - Section 2 - 1:00 pm
 *
 * @par Location:
 *         McLaury - Room 313
 *
 * @section program_section Program Information
 *
 * @details This program simulates placing boxes on conveyor belts of different 
 *          widths. The user enters, on the command line, the program name, the
 *          file to read information from, and the lengh that every belt will 
 *          be.
 *
 *          This program checks the command line arguments to make sure that 
 *          there are 3 of them. After confirming this, the program attempts to 
 *          open the file and read from it. The file contains the width that  
 *          the 3 belts will be; as well as the width, depth, and height of each 
 *          package. The file will contain -1, -1, -1 to represent a simulation
 *          end and 0,0,0 to represent the end of the all simulations. 
 *          
 *          The program will read from this file deciding on which of the three
 *          belts it will place a particular box. If the both the depth and the 
 *          width of a package can fit on a belt, the program will choose the 
 *          one that takes up the least space lenthwise on the the belt. Every 
 *          time a box is placed on a belt, the program checks to see if the 
 *          "earliest" package is hanging more than half over the end of the  
 *          belt. If it is, that package is removed from our belt and outputed 
 *          to a file, with the name of the belt that it was on.  
 *          
 *          
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   Usage: <program name> (input filename) belt_length
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *
 * @par Modifications and Development Timeline:
   @verbatim 
   @par Credits
   <a href="https://gitlab.mcs.sdsmt.edu/csc215s18prog4/team14/commits/master">Gitlab log link</a>
   @endverbatim
 *
 ******************************************************************************/
#include "belt.h"
#include <iostream>

using namespace std;

/*************************************************************************//**
 * @author Benjamin Braun, Nathaniel Fagrey, Matthew Reff
 * 
 * @par Description: 
 * This function mainly serves as a place to call all the other functions. It 
 * also prints out the simulation that we are on. 
 * 
 * @param[in]      argc - number of the arguments on the command line
 * @param[in]      argv - holds all the commands entered on the command line
 * 
 * @returns 0 program ran successful.
 * @returns -1 wrong number of arguments entered
 *
 ****************************************************************************/
int main(int argc, char * argv[])
{
    int beltWidthA, beltWidthB, beltWidthC, boxWidth, boxHeight, boxDepth;
    int beltLength, simNum = 1, boxNum;
    ifstream inputFile;
    ofstream outFile;
    conveyorBelt A, B, C;
    box package;
    char belt;

    //check arguments
    if (!checkArguments(argc, argv[2]) )
        return -1;
    
    // get belt length
    beltLength = stoi( argv[2], 0 );
    // open input file
    openInputFile(inputFile, argv[1]);
    // open output file
    openOutputFile( outFile, "run.out");
    // while valid conveyor dimensions are given
    while ( getConveyorDimensions( beltWidthA, beltWidthB, beltWidthC, 
        inputFile ) )
    {
        // print simulation number
        printSim ( outFile, simNum );
        // reset box number
        boxNum = 1;
        // set properties of belts
        A.addtoConveyor( beltWidthA, beltLength, 'A' );
        B.addtoConveyor( beltWidthB, beltLength, 'B' );
        C.addtoConveyor( beltWidthC, beltLength, 'C' );
        // sort the belts by width
        sortBelt( A, B, C );
        // while valid box dimensions are given
        while ( getBoxDimensions(boxWidth, boxHeight, boxDepth, inputFile ) )
        {
            // sets details of package  
            addToPackage( package, boxWidth, boxHeight, boxDepth, boxNum );
            
            // sort box dimension for ease of use
            sortBox( package );
            // chooses which belt for the package
            belt = addToBelt( package, A, B, C );
            if ( belt == 'A')
            {   
                // adds package to belt and checks for any packages to fall
                A.addBox( package );
                A.boxFalls( outFile );
            }
            else if ( belt == 'B' )
            {
                // adds package to belt and checks for any packages to fall
                B.addBox( package );
                B.boxFalls( outFile );
            }
            else if ( belt == 'C' )
            {
                // adds package to belt and checks for any package to fall
                C.addBox( package );
                C.boxFalls( outFile );
            }
            ++boxNum;
        }
        //clear belts
        A.clearBelt();
        B.clearBelt();
        C.clearBelt();
        simNum++;
    }
    return 0;
}