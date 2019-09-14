/*************************************************************************//**
 * @file
 * @brief header file for srt.cpp file
****************************************************************************/
#ifndef _SRT_H
#define _SRT_H
#include<string>
#include<iostream>
#include<fstream>
#include<ostream>
using namespace std;


/*!* @brief allows access to all the functions that manipulate the linked list
*/
class srtList
{
    public:
        srtList();
        ~srtList();

        bool insert( string startingTime, string endingTime, 
            string theCaption );

        bool remove( int frame );
        bool retrieve( int frame, string &startingTime, string &endingTime,
            string &theCaption );
        bool update( int frame, string theCaption );
        void printSrt(ostream &out);
        int size();
        
        
       
     private:
        
        /*!* @brief contains all the information about a frame in the SRT 
        file */
        struct node
        {
            string startTime; /*!< the start time of the frame */
            string endTime;   /*!< the end time of the frame */
            string caption;   /*!< the caption of the frame */
            node *next;       /*!< contains the addresss of the next node in 
                               the linked list */
        };

        
        node *headPtr;   /*!< a pointer to first node in the linked list */ 
};


bool checkArgcVal(int num);

bool validateTime(string item);

void readInList(ifstream &fin, srtList &myinsert);

bool GetFunctions(int choice, srtList &linkedList, string file, ofstream 
    &fout);

bool printRange(ostream &out, srtList &srt, int startFrame, int endFrame);


#endif



