/*************************************************************************//**
* @file
*
* @mainpage Program 4 - Harp Heroine
*
* @section course_section Course Information
*
* @author Nathaniel Fagrey
*
* @date December 04, 2017
*
* @par Professor:
*         Professor Kelly Corwin 
*
* @par Course:
*        CSC 150 - M003 -  3:00PM
*
* @par Location:
*         Engineering and Physics Building - Room 253
*
* @section program_section Program Information
*
* @details This program attempts to produce sound electronically by imita-
*          ting actual physical strings. It does this by using the Klarplus 
*          Strong Algorithm. This algorithm works by averaging and summing 
*          random numbers in a 2D array.  
*          
*          The program first gets the necessary information from the user, by 
*          inputing the file of the song he/she would like to play. These
*          files contain the time for each note played, the note number
*          (called the MIDI number), and the volume the song is to
*          be played at. 
*       
*          Using this information, the program is able to play the song by fill-
*          ing the row on a 2D array that corresponds to the MIDI note with 
*          random numbers. These random numbers are then averaged, multiplied 
*		   by a decay factor of 0.966, and added down the columns. The 
*		   artificial length of columns for a given row is determined by an 
*		   equation that divides the rate (44100 per sec) by the fundamental 
*          frequency of that note.
*
*		   After summing through one column, the sum is outputed to a file. The
*		   summing of the columns happens 441 times for every centisecond which 
*		   is given by the input file. The program then takes all these outputed 
*		   sums and converts them into a wav file, which is then played by the 
*		   computer.
*
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      None
*
* @par Usage:
@verbatim
C:\Users\7416949\Documents\SDSMT\Fall 2017\CSC150\Programs\prog4\
* program4\prog4.cpp
*
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Nov 23, 2017  Came up with the basic algorithm
Nov 28, 2017  Discovered that the previous algorithm was incorrect. 
Nov 28, 2017  Began to develope the correct algorithm
Nov 30, 2017  Got the right basic algorithm 
Dec 1, 2017   Program up and running
*****************************************************************************/

#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cctype>
#include<ctime>
#include "wave.h"
using namespace std;

//calculates string_length 
void calc_string_length( int string_length[] );

/*reads in file and calls functions to fill with random numbers and 
update strings */
void pluck_string( ifstream &input, ofstream &output, double buffer[][5395],
	int string_length[], double &tempo, int position[] );

//fills the buffer row that corresponds to the MIDI note with random numbers
void fill_with_rand( double buffer[][5395], int string_length[], int midi, 
	                double volume );

//updates the strings by using the Karplus Strong Algorithnm 
void update_strings( ofstream &output, double buffer[][5395],
	int string_length[], int time, double &tempo, int position[] );


/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function takes in the program name, file name, and the tempo for the 
* song that is to be played. It then opens the input and output files. Last,
* it calls the necessary functions to convert the numbers from the input file
* into numbers that can be converted into a wav file. 
*
* @param[in]     argc - the number of arguments in the command line
* @param[in]     argv[] - stores all the arguments in the command line
*
* @returns 0 program ran successful.
* @returns -1 the program failed or there was an error.
*****************************************************************************/

int main(int argc, char* argv[])
{
	ifstream input;
	ofstream output;
	
	int i = 0; 
	
	char file_name[100]; //the filename we copy onto from argv
	
	int string_length[5395] = { 0 }; //length of each string
	
	static double buffer[128][5395] = { 0 }; //the buffer for the note strings
	
	int midi = 0; //MIDI note

	double tempo = 1.0; //the tempo the note is to be played at
	
	int int_val = 0; //just an integer val for the convert to wave function
	
	int position[128] = { 0 }; //keeps track of the postion in a buffer row
	
	srand(7843);
	
	//argc must be between 2 and 3 inlcusive
	if ( ( argc < 2 ) || ( argc > 3 ) )
	{
		cout << "Incorrect number of arguments entered. " << endl;

		return -1;
	}
		
	//copies argv to file_name 
	strcpy( file_name, argv[1] );
	
	//tempo equals argc[2] or its default is 1
	if ( argc == 3 )
	{
		//changes the tempo input from string to double 
		tempo = atof( argv[2] );
	}
		
	//tempo range requirments
	if ( ( tempo > 4 ) || ( tempo < 0.25 ) )
	{
		cout << "Error: tempo must be between 0.25 and 4. " << endl;

		return -1;
	}
	
	
	//opens input file
	input.open( file_name );

	//makes sure file is open
	if ( !input.is_open() )
	{
		cout << "Error: Unable to open and/or find file. " << endl;

		return -1;
	}
	
	
	//opens output file
	output.open( "temp_data" );

	//makes sure input file opens
	if ( !output.is_open() )
	{
		cout << "Error: Unable to open file. " << endl;

		return -1;
	}
	
	
	//call function to calculate the length of each string
	calc_string_length( string_length );
	
	//"plucks" the strings, which enables us to eventually play them
	pluck_string( input, output, buffer, string_length, tempo, position );

	//fns the "." in the filename in oder to find the place to add .wav to it
	for (i = 0; i < ( strlen( file_name ) ); ++i)
	{
		if ( file_name[i] == '.' )
		{
			file_name[i] = 0;
		}
	}
	
	//new file name
	strcat( file_name, ".wav" );

	//converts to a wav file in order to play it 
	int_val = convert_to_wave( "temp_data", file_name, 44100 );
	
	//close input file
	input.close();
	
	//close output file
	output.close();
	
	return 0;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function calculates the length of each row in the buffer array.
* The equation to do this is 44100 / ( ( pow(2, ( ( k - 69 ) / 12.0 ) ) * 
* 440 ) ) ), in which the numerator is the the sampling rate and the denominator 
* is the  fundimental frequency, dependent on k, the MIDI note. These notes go 
* from 1 to 128, with a unique row length in the buffer array for each one.
*
* @param[in,out]  string_length[] - an array that holds the length of each row
*                                   in the buffer array for a MIDI note 
*                                   (1 through 128).
*
*****************************************************************************/

void calc_string_length( int string_length[] )
{
    double k;
	
	int midi = 0; // refers to midi number
		
	    //calculates the string length for a particular row in buffer array
	    for ( k = 0; k < 128; ++k )
		{

			string_length[midi] = round( 44100 / ( ( pow(2, ( ( k - 69 ) 
				                  / 12.0)) * 440)));
			++midi;
		
		}
}
/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function simulates the plucking of strings. It reads in each 
* line of the file, calling a function to fill the row that 
* corresponds to the inputed MIDI note with random numbers. It also calls a 
* function to update that array. It continues to read from the file, until
* the MIDI note = -1.
* 
*
* @param[in,out]  input - file input variable 
* @param[in,out]  output - file output variable 
* @param[in,out]  buffer[][5395] - buffer array that simulates the strings 
*                                  of a harp
* @param[in,out]  string_length[] - lengths of each row in the buffer array
* @param[in,out]  tempo - speed at which the song is to be played at, default
*                         value is 1.
* @param[in,out]  postion[] - the place where we are at in a particluar row
*                             at a particular time 
*
*****************************************************************************/

void pluck_string( ifstream &input, ofstream &output, double buffer[][5395],
	              int string_length[], double &tempo, int position[] )
{
	
	int  midi; //the note to be played
	
	double volume; //the voume is the range we get random numbers from 
	
	int time[2] = { 0 }; //keeps track of the time interval to play a note
	
	int total_time = 0; //the time to play a certain note 

	int i = 0;
	
	//read in the first time 
	input >> time[0];

    do 
	{
		
		//reads in input
		input >> midi >> volume >> time[1];

		//ends the function if midi = -1
		if ( midi == -1 )
		{
			return;
		}
		
		//calculates the time to be played for each midi note
		total_time = time[1] - time[0];

		//places the value from element 1 to 0
		time[0] = time[1];

		//fills array with rand numbers
		fill_with_rand( buffer, string_length, midi, volume );

		//function to update array using averages and sums
		update_strings( output, buffer, string_length, total_time, 
			tempo, position );
	
	} while ( !input.eof() );

}
/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function fills the buffer row that corresponds to the read in MIDI note
* with random numbers. The random numbers are selected from the range of 
* numbers specified by the inputed volume ( if volume = 1, random numbers 
* between -0.5 and 0.5).
* 
*
* @param[in,out]  buffer[][5395] - buffer array that simulates the strings 
*                                  of a harp
* @param[in,out]  string_length[] - lengths of each row in the buffer array
* @param[in]      midi - the note read in from the file
* @param[in]      volume - the volume specifies the range of random numbers 
*                          we read into the file. 
*
*****************************************************************************/

void fill_with_rand( double buffer[][5395], int string_length[], 
	int midi, double volume )
{
	
	int j = 0;

		//fills a particular string with rand numbers
		for ( j = 0; j < string_length[midi]; ++j )
		{
			//random number generator 
			buffer[midi][j] = ( ( double(rand() ) / RAND_MAX) - (1 / 2.0 ) ) 
				* volume;
		}
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function "updates" the array that has rows filled with random numbers.
* The function goes through each row in the array taking the average for each 
* consecutive elements in all the rows and multilying that average by a decay 
* factor of 0.996. These averages are then summed through the columns 441 times
* for every centisecond that was read in from the file. Because the each row in 
* the buffer array is different, we use the remainder of the postion and 
* the string_length to keep track of where we are in the array, looping back 
* when we reach the end of a row.
* 
* @param[in,out]  output - file output variable 
* @param[in,out]  buffer[][5395] - buffer array that simulates the strings 
*                                  of a harp
* @param[in,out]  string_length[] - lengths of each row in the buffer array
* @param[in]      time[] - the time in centiseconds that each note is to played
*                          for
* @param[in,out]  tempo - speed at which the song is to be played at, default
*                         value is 1.
* @param[in,out]  postion[] - the place where we are at in a particluar buffer 
*                             row at a particular time 
*
*****************************************************************************/

void update_strings( ofstream &output, double buffer[][5395], 
	int string_length[], int time, double &tempo, int position[] )
{
	
	int i, k, l = 0; //counters
	
	double sum = 0.0; //sum of the averages
	
	//time for a note, dependent on the tempo
	for ( l = 0; l < time / tempo; ++l )
	{
		//outputs 441 sums for every centisecond 
		for ( i = 0; i < 441; ++i ) 
		{
			//going through all the rows
			for ( k = 0; k < 128; ++k )
			{

				//Klarplus Strong Algorithm
				buffer[k][position[k] % string_length[k]] = 0.996 *
					( ( buffer[k][position[k] % string_length[k]] + 
					buffer[k][(position[k] + 1) % string_length[k]] ) / 2.0 );
				
				//sum averages
				sum += buffer[k][position[k] % string_length[k]];
				
				//position must move as well
				++position[k];
			}
			
			//output to temp_data the sum of all the averages for a column
			output << sum << endl;
		     
			//sum must start at 0 for each column
			sum = 0.0;
		}

	}

}