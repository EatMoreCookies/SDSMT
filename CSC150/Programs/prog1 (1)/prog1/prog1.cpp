
/*************************************************************************//**
 * @file 
 *
 * @mainpage Program 1 - Musical Notes
 * 
 * @section course_section Course Information 
 *
 * @author Nathaniel Fagrey
 * 
 * @date September 15, 2017
 * 
 * @par Professor: 
 *         Professor Kelly Corwin 
 * 
 * @par Course: 
 *         CSC 150 - Section 3 -  3:00 pm
 * 
 * @par Location: 
 *         Engineering and Physics Building - Room 253
 *
 * @section program_section Program Information 
 * 
 * @details This program attempts to convert the notes of the 
 *          piano into their individual frequencies. In order to do this we  
 *			must use the equation f = x * pow(2, (w + m/12)). 
 *
 *          F is the frequency of the actual piano note, x in the fequency of a 
 *          reference note, w is the difference between the octive entered and   
 *          the reference octive, and m is the difference between the the  
 *          seminote entered and the reference seminote.
 * 
 *          After converting the notes into their frequencies, the program 
 *          will then actually produce those frequencies as audio. For this 
 *          program we will use the reference octive pitch-class (octpch) 4.9,
 *          where 4 is the octive and 9 is the seminote or pitch-class.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      None: no special compiling was done.  
 * 
 * @par Usage: 
   @verbatim  
   c:\> <prog>.exe 
   d:\> c:\bin\<prog>.exe 
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug <List anything that is not working in your program>
 * @bug <one item per line with tag>
 * 
 * @todo Everything!
 * @todo <one item per line with tag>
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Sep 2, 2017   Program was created.
   Jan 15, 2011  What I did on this date
                 can use additional lines
   Jan 18, 2011  What I did on this date
   Jan 19, 2011  What I did on this date
   @endverbatim
 *
 *****************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
using namespace std;

 

/**************************************************************************//** 
 * @author Nathaniel Fagrey
 * 
 * @par Description: This function will calculate the frequency for the
 * octive pitch-classes. 
 * 
 * @returns 0 program ran successful.
 
 *****************************************************************************/

int main()
{
	int reference_octive = 4;   // refernce octive
	int reference_seminote = 9;    // reference note
	int x = 440;             
	/*x refers to the frequency of the reference octive pitch class that we    
    selected*/
	double frequency1 = 0.0;
	double frequency2 = 0.0;
	double frequency3 = 0.0;
	int octive_input = 0;
	int seminote_input = 0;
	double w = 0;               // w refers to difference between octaves
	double m = 0;        //  m refers to the difference between seminotes
	int Duration = 500;
	
	
	cout << "Enter the octave of the first note: ";  // asking user for inputs
	     cin >> octive_input;
	cout << "Enter the pitch class of the first note: ";
	     cin >> seminote_input;

	w = octive_input - reference_octive;
	m = seminote_input - reference_seminote;

	frequency1 = x * pow(2, (w + m / 12)); // equation to calculate frequency


	cout << "Enter the octive of the second note: ";      //asking for user inputs
	     cin >> octive_input; 
	cout << "Enter the pitch class of the second note: ";
	     cin >> seminote_input;

	w = octive_input - reference_octive;
	m = seminote_input - reference_seminote;
	
	frequency2 = x * pow(2, (w + m / 12)); // equation to calculate frequency
	

	cout << "Enter the octive of the third note: ";      //asking for user inputs
	     cin >> octive_input;
	cout << "Enter the pitch class of the third note: ";
	     cin >> seminote_input;

	w = octive_input - reference_octive;
	m = seminote_input - reference_seminote;
	
	frequency3 = x * pow(2, (w + m / 12)); // equation to calculate frequency
	
	cout << "Note 1: " << frequency1 << "Hz" << endl; 
	Beep(int(frequency1),  int(Duration));
	cout << "Note 2: " << frequency2 << "Hz" << endl;
	cout << "Note 3: " << frequency3 << "Hz" << endl;
	
	
	return 0;

}

