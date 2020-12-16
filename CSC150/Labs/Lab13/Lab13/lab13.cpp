//  CSC 150  Lab 13  Command line args, file reading/writing


#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

const int MAX = 100;


bool find_word( char str[], char tgt[] );



int main(              )
{
	char strings[MAX][81] = { "" };
	char target[81];
	
	//more variables
	
		
	
	//test arguments, exit if incorrect number
		
		
		
	//test for /a  append flag	
	
	
	
	//open and test files
	
	
	
	//read text into string array
	
		
	
	//get word to search for
	
	
	
	//test for word in each string, write found strings to file
	
		
	
	//display number of strings written

    return 0;
}

/*
 * find_word - finds first occurence of a word within a string.
 * target word must be delimited by non-alphabetic characters (a whole
 * word match).
 * 
 * returns true if found, false otherwise
 * 
 * This is not the most elegant method, especially the use of the [-1]
 * index. But for this lab, it should suffice.
*/
bool find_word( char str[], char tgt[] )
{
	bool found = false;
	int tgtlen = strlen( tgt );
	int srclen = strlen( str );
	char* start = str;
	
	while( tgtlen <= srclen  && !found )
	{
		if( strnicmp( start, tgt, tgtlen ) == 0 && !isalpha(start[tgtlen] )
			 && !isalpha( start[-1] ) )
		{
			found = true;
		}
		else
		{
			start++;
			srclen = strlen( start );
		}
	}
	
	return found;
}
