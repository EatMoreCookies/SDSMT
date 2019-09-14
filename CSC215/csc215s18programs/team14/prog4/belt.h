/*************************************************************************//*
* @file header file for all the belt functions
****************************************************************************/
                                                                           
#ifndef _BELT_H_
#define _BELT_H_

#include "unsortedDouble.h" 
#include <fstream>
using namespace std;



/*! @brief this struct holds all the information for a box */
struct box 
{
    int boxNumber;  /*!< the number of the box*/
    int width;      /*!< the width of the box */
    int depth;      /*!< the depth of the box*/
    int height;     /*!< the height of the box*/

    bool operator==(box &package);  /*!< overloaded function for structs */
}; 



/*! @brief this class holds our conveyor belt */
class conveyorBelt
{   public:
    conveyorBelt();
    ~conveyorBelt();
    bool addBox ( box  &package );
    bool removeBox ( box &package );
    bool retrieveFirst ( box &package );
    friend char addToBelt (box &package, conveyorBelt &A, conveyorBelt &B, 
        conveyorBelt &C );
    
    void boxFalls( ostream &out );
    void addtoConveyor( int width, int length, char let );
    void clearBelt();

    bool operator<( conveyorBelt &belt );

    private:
    unsortedDouble<box> theBelt; /*!< doubly linked list for our queue*/
    int theLength;               /*!< length of the belt*/
    int theWidth;                /*!< the width of the belt */
    int space;                   /*!< the space taken up on the belt*/
    char letter;                /*!< which belt this is */
 };

 
 bool getBoxDimensions(int &width, int &length, int &height, ifstream &infile);
 bool getConveyorDimensions(int &beltA, int &beltB, int &beltC, 
     ifstream &infile);
 
 bool checkArguments(int argCount, char *beltLength);
 void sortBelt( conveyorBelt &small, conveyorBelt &medium, 
     conveyorBelt &large );
 
 void sortBox(box &ubox);
 void openInputFile(ifstream &infile, char fileName[]);
 void printToFile(ostream &out, box package, char conveyor);
 void printToFile( ostream &out, box package, char conveyor );
 void addToPackage ( box &package, int width, int height, int depth, 
     int boxNum );
 
 void openOutputFile( ofstream &outfile, string fileName );
 void printSim ( ostream &out, int simNum );
 

#endif