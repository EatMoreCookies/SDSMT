
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
* @details This program converts the notes of the
*          piano into their individual frequencies and plays them as audio.
*		   In order to do this we must use the
*          equation f = x * pow(2, (w + m/12)).

*          F is the frequency of the piano note, x in the fequency of a
*          reference note, w is the difference between the octave entered and
*          the reference octave, and m is the difference between the the
*          seminote (or pitchclass) entered and the reference seminote
*          (or pitchclasss).
*
*          After converting the notes into their frequencies, the program
*          will then actually produce those frequencies as audio. For this
*          program we will use the reference octave 4 and seminote 9. The
*          frequency for this note is 440 Hz. This is our reference
*          frequency.
*
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      None: no special compiling was done.
*
* @par Usage:
@verbatim
c:\Users\7416949\Documents\SDSMT\Fall 2017\CSC150\Programs\prog1\Program1
  \prog.cpp
*
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Sep 2, 2017   Program was created.
Sep 6, 2017   Played the notes as audio from the computer
Sep 11, 2017  Started using branches to restrict the inputs
Sep 13, 2017  Finished program
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
* @par Description: This function will calculate the frequency of multiple
* notes and play them audio.
*
* @returns 0: program ran successful.
* @returns 1: invalid user input.
* @returns 2: Frequency out of range. 

*****************************************************************************/


int main()
{

	int Duration = 500;          //the amount of time the audio will play
	double frequency1 = 0.0;     //frequency of the first note.
	double frequency2 = 0.0;     //frequency of the second note.
	double frequency3 = 0.0;    //frequency of the third note.
	double diff_of_pitchclass = 0;  //difference between seminotes (pitchclass)
	int octave_input1 = 0;
	int octave_input2 = 0;
	int octave_input3 = 0;
	int pitchclass_input1 = 0;
	int pitchclass_input2 = 0;
	int pitchclass_input3 = 0;
	int reference_octave = 4;     //refernce octave which is arbitrarily chosen
	int reference_pitchclass = 9; /* reference seminote (pitchclass), which is
								  chosen arbitrarlily */
	double diff_of_octaves = 0;   //difference between octaves
	int x = 440;                  /* x refers to the frequency of the reference
								  and octive pitch class that we selected */





	// asking user for inputs
	cout << "Enter the octave of the first note: ";

	    cin >> octave_input1;

	    //restricts user input
	    if ( octave_input1 > 10 )
	    {
			cout << "Error: invalid input" << endl;
			return 1;
	    }

	//asks for user inputs
	cout << "Enter the pitch class of the first note: ";

	    cin >> pitchclass_input1;

	    //restricts user inputs
	    if ( pitchclass_input1 > 11 )
	    {
			cout << "Error: invalid input" << endl;
			return 1;
	    }

	//calculates the difference of octives
	diff_of_octaves = octave_input1 - reference_octave;

	//calculates the difference of pitchclasses
	diff_of_pitchclass = pitchclass_input1 - reference_pitchclass;

	// equation to calculate frequency
	frequency1 = x * pow(2, ( diff_of_octaves + diff_of_pitchclass / 12));
	    
	    //check to see if frequency is in range
	    if ( ( frequency1 <= 37 ) || ( frequency1 >= 30, 000 ) )
	    {
		    cout << "Error: frequency out of range. " << endl;
		    return 2;
	    }


	//asking for user inputs
	cout << "Enter the octive of the second note: ";

	    cin >> octave_input2;

	    //restricts user inputs
	    if ( octave_input2 > 10 )
	    {
			cout << "Error: invalid input" << endl;
			return 1;
	    }

	//asking for user inputs		
	cout << "Enter the pitch class of the second note: ";

	    cin >> pitchclass_input2;

	    //restricts user inputs 
	    if ( pitchclass_input2 > 11 )
	    {
			cout << "Error: invalid input" << endl;
			return 1;
	    }

	//calculates the difference of octives
	diff_of_octaves = octave_input2 - reference_octave;

	//calculates the difference of pitchclasses
	diff_of_pitchclass = pitchclass_input2 - reference_pitchclass;

	//equation to calculate frequency
	frequency2 = x * pow(2, ( diff_of_octaves + diff_of_pitchclass / 12));
	    
	    //check to see if frequency is in range
	    if ( ( frequency2 <= 37 ) || ( frequency2 >= 30, 000 ) )
	    {
		    cout << "Error: frequency out of range. " << endl;
		    return 2;
	    }


	//asking for user inputs
	cout << "Enter the octive of the third note: ";

	    cin >> octave_input3;

	    //restricts user inputs
	    if ( octave_input3 > 10 )
	    {
			cout << "Error: invalid input" << endl;
			return 1;
	    }

	// asking for user inputs 
	cout << "Enter the pitch class of the third note: ";

	    cin >> pitchclass_input3;

	    //restricts user inputs
	    if ( pitchclass_input3 > 11 )
	    {
			cout << "Error: invalid input" << endl;
			return 1;
	    }

	//calculates the difference of octives
    diff_of_octaves = octave_input3 - reference_octave;

	//calculates the difference of pitchclasses
	diff_of_pitchclass = pitchclass_input3 - reference_pitchclass;

	// equation to calculate frequency
	frequency3 = x * pow(2, ( diff_of_octaves + diff_of_pitchclass / 12));
	    
	    //check to see if frequency is in range
	    if ( ( frequency3 <= 37 ) || ( frequency3 >= 30, 000 ) )
	    { 
			cout << "Error: frequency out of range. " << endl;
			return 2;
		}
	
	
    //outputing original octive and pitchclasses along with the frequency
	cout << "Note 1: " << octave_input1 << "." << pitchclass_input1 << " is "
		<< frequency1 << " Hz" << endl;

	//function to play the note as audio
	Beep( int( frequency1 ), int( Duration ) );

	//outputing original octive and pitchclasses along with the frequency
	cout << "Note 2: " << octave_input2 << "." << pitchclass_input2 << " is "
		<< frequency2 << " Hz" << endl;

	//function to play the note as audio
	Beep( int( frequency2 ), int( Duration ) );

	//outputing original octive and pitchclasses along with the frequency
	cout << "Note 3: " << octave_input3 << "." << pitchclass_input3 << " is "
		<< frequency3 << " Hz" << endl;

	//function to play the note as audio
	Beep( int( frequency3 ), int( Duration ) );


	return 0;

}

