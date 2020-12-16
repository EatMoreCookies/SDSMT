
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
*          piano into their individual frequencies and play them as audio.
*		   In order to do this we must use the
*          equation f = x * pow(2, (w + m/12)).

*          F is the frequency of the actual piano note, x in the fequency of a
*          reference note, w is the difference between the octive entered and
*          the reference octive, and m is the difference between the the
*          seminote (or pitchclass) entered and the reference seminote
*          (or pitchclasss).
*
*          After converting the notes into their frequencies, the program
*          will then actually produce those frequencies as audio. For this
*          program we will use the reference octive 4 and seminote 9. The
*          frequency for this note is 440 Hz. This is our reference fre-
*          quency.
*
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
*
* @todo Still have to restrict the inputs a user is allowed to enter
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Sep 2, 2017   Program was created.
Sep 6, 2017   PLayed the notes as audio from the computer
Sep 11, 2017  
@endverbatim
*
*****************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <cctype>
using namespace std;



/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description: This function will calculate the frequency and play the
* notes on a piano.
*
* @returns 0 program ran successful.
* @returns 1 invalid user input.

*****************************************************************************/

int main()
{
	int reference_octive = 4;   // refernce octive
	int reference_seminote = 9;    // reference note
	int x = 440;
	/*x refers to the frequency of the reference and octive pitch class that we
	selected*/
	double frequency1 = 0.0;
	double frequency2 = 0.0;
	double frequency3 = 0.0;
	int octive_input = 0;
	int pitchclass_input = 0;
	double w = 0;               // w refers to difference between octaves
	double m = 0;        //  m refers to the difference between seminotes
	int Duration = 500;


	
	cout << "Enter the octave of the first note: ";  // asking user for inputs
	     cin >> octive_input;
		     if (octive_input > 10)
			 {
				 return 0;
		     }
	cout << "Enter the pitch class of the first note: ";
	     cin >> pitchclass_input;
		     if (pitchclass_input > 11)    //the user inputs must be 
		     {
			cout << "ERROR. Pitch class input must less or equal to 11."
				<< endl;
		     }


    w = octive_input - reference_octive;
	m = pitchclass_input - reference_seminote;

	frequency1 = x * pow(2, (w + m / 12)); // equation to calculate frequency
	
		cout << "Enter the octive of the second note: ";      //asking for user inputs
	     cin >> octive_input;
		     if (octive_input > 10) 
			 {
			 cout << "ERROR. Octive input must less or equal to 10." << endl;
		     }
	cout << "Enter the pitch class of the second note: ";
	     cin >> pitchclass_input;
		     if (pitchclass_input > 11)
		     {
			 cout << "ERROR. Pitch class input must less or equal to 11."
				 << endl;
		     }

	w = octive_input - reference_octive;
	m = pitchclass_input - reference_seminote;

	frequency2 = x * pow(2, (w + m / 12)); // equation to calculate frequency


	cout << "Enter the octive of the third note: ";      //asking for user inputs
	     cin >> octive_input;
		     if (octive_input > 10) 
			 {
			 cout << "ERROR. Octive input must less or equal to 10." << endl;
		     }
	cout << "Enter the pitch class of the third note: ";
	     cin >> pitchclass_input;
		     if (pitchclass_input > 11)
		     {
			 cout << "ERROR. Pitch class input must less or equal to 11."
				 << endl;
		     }

	w = octive_input - reference_octive;
	m = pitchclass_input - reference_seminote;

	frequency3 = x * pow(2, (w + m / 12)); // equation to calculate frequency

	cout << "Note 1: " << frequency1 << "Hz" << endl;
	Beep(int(frequency1), int(Duration)); //function to play the note as audio

	cout << "Note 2: " << frequency2 << "Hz" << endl;
	Beep(int(frequency2), int(Duration)); //function to play the note as audio

	cout << "Note 3: " << frequency3 << "Hz" << endl;
	Beep(int(frequency3), int(Duration)); //function to play the note as audio


	return 0;

}

