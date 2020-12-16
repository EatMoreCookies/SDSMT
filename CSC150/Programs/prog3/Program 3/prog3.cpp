/*************************************************************************//**
* @file
*
* @mainpage Program 3 - Voting
*
* @section course_section Course Information
*
* @author Nathaniel Fagrey
*
* @date October 29, 2017
*
* @par Professor:
*         Kelly Corwin
*
* @par Course:
*         CSC 150 - MOO3 -  3:00PM
*
* @par Location:
*         Electrical and Engineering Building - Room 253
*
* @section program_section Program Information
*
* @details This program attempts to show how the counting error in an
* electronic voting machine can have on an election's outcome. 
* In order to do this, the program asks the user to input the necessary 
* information to calculate the effects. 
*
* The necessary information includes the amount of total votes, the margin by
* which one canadate won over the other, and the error that a machine has
* in counting the votes. The number of votes has to be greater
* than 1, the margin has to be between 1% and 50%, and the machine error has to 
* be between 1% and 100%.
*
* The program then takes this info and runs 500 simulations of the election, 
* keeping track of how many votes are incorrectly switched from one canidate to
* the other due to machine error. If the amount of votes that are switched is  
* greater or equal to the margin, the candidate that was supposed to lose will
* actually win. The program then outputs a summary of the process, including
* the amount of flipped elctions and error rate of those elections. 
* 
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      No special compiling instructions
*
* @par Usage:
@verbatim
C:\Users\7416949\Documents\SDSMT\Fall 2017\CSC150\Programs\prog3\Program 3\
prog3.cpp
*
@endverbatim
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
October 16, 2017  Started defining functions
October 16, 2017  Got the first function working. 
October 23, 2017  All functions up and running. 
*****************************************************************************/


#include<iostream>
#include<cmath>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;

/*!
* @brief The number of trials we run for each election
*/
const int trials = 500;


//Gets the necessay info for the election
void get_params( double &num_votes, double &margin, double &machine_error );

//Calculates the amount of votes that each candidate got with the machine error 
void do_voting( int votes[][2], int trials, double num_votes, double margin,
	double machine_error );

//Calculates how many elections went the wrong way and the error percentage
void calc_error( int votes[][2], int trials, int &flipped_elections,
	double &percent_error );

/* Displays the summary of the whole processes and asks the user if they want to
 run another election */
void display_summary(int trials, double num_votes, double margin,
	double machine_error, int flipped_elections, double percent_error);

//Gets the user choice if they want to run another simulation 
char get_choice( );


/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function calls the other functions and serves as a transer point of
* variables. 
*
* @returns 0 program ran successful.
*****************************************************************************/

int main()
{
	//user choice to continue. Must be outside loop to work
	char choice = '?';
	
	/*declarations inside the do-while loop to ensure a reset of variables if 
	the user runs another simulation */
	do
    {
		//number of votes
		double num_votes = 0.0;   
		
		//margin of the election
		double margin = 0;     
		
		//machine error
		double machine_error = 0; 
		
		//stores the votes for both canidates
		int votes[trials][2];   
		
		//the amount of elections that went the wrong way
		int flipped_elections = 0;  
		
		//the percentage error calculated using the number of flipped elections
		double percent_error = 0.0;
		 
		//random seed
		srand(int(time(NULL)));
	
				//calls get_params
				get_params(num_votes, margin, machine_error);
  
				//calls do_voting
				do_voting(votes, trials, num_votes, margin, machine_error);

				//calls calc_error 
				calc_error(votes, trials, flipped_elections, percent_error);

				//calls display_summary
				display_summary(trials, num_votes, margin, machine_error, 
					flipped_elections, percent_error);
				
				//calls get_choice to get user choice to run another simulation
				choice = get_choice();

    } while (choice == 'Y');
	
	
	return 0;
}


/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function prints an informative message and takes in input values from 
* the user making sure they are in the allowed range.  
*
* @param[in,out]     num_votes - total number of votes for a given election
* @param[in,out]     margin - the amount canidate A won over canidate B 
* @param[in,out]     machine_error - the counting error that a given electronic 
*                                    voting machine has. 
* @returns none
*****************************************************************************/
void get_params( double &num_votes, double &margin, double &machine_error )
{
	//explanation of the parameters to enter
	cout << "------------------" << endl
		<< "Enter voting simulation parameters. All values must be positive"
		<< endl << "and greater than 0. Margin and error are entered as "
		<< endl << "percentages (do not use the % sign). Margin cannot "
		<< endl << "exceed 50% and error cannot exceed 100% " << endl
		<< endl;
	
	//gets number of votes
	do {
		cout << "Enter the number of votes: ";

		    cin >> num_votes;
			
				if ( num_votes < 1 )
				{
					cout << "Error: Number of votes needs to be greater than 1 "
						 << endl;
				}

	    } while ( num_votes < 1 );

    //gets election margin
	do {
	   cout << "Enter election margin percentage: ";

	       cin >> margin;
	
			   if ( ( margin < 1 ) || ( margin > 50 ) )
				{
					cout << "Error: Election margin must be between 1 and 50 "
						 << endl;
                }
			
       } while ( ( margin < 1 ) || ( margin > 50 ) );

	//gets machine error percentage		
    do {
	    cout << "Enter voting machine percentage error: ";

			cin >> machine_error;
		
				if ( ( machine_error < 1 ) || ( machine_error > 100 ) )
				{
					cout << "Error: Election machine percentage error must be "
						 "between 1 and 100" << endl;
				}

		} while ( ( machine_error < 1 ) || ( machine_error > 100 ) );

} 

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function runs 500 trials of a given election. After calculating how 
* many votes the winning canidate should get (called canidate A) and how many 
* votes the losing canidate should get (called canidate B), the function then 
* runs the election with the machine error to see how many votes are added to 
* the wrong canidate. It then stores the votes in a array. 
*
* @param[in]      trials - the amount of we trials run for a given election. 
* @param[in]      num_votes - number of votes in the election
* @param[in]      margin - the amount canidate A won over canidate B
*
* @param[in,out]  votes[][2] - stores the amount of votes that each canidate 
*                              got with the machine error. 
* @returns none
*****************************************************************************/
void do_voting(int votes[][2], int trials, double num_votes, double margin,
	double machine_error)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int winners_votes = 0;    //votes the winner A should get
	int losers_votes = 0;   //votes the loser B should get
	int votes_for_A = 0;    //the actual votes for A in the election
	int votes_for_B = 0;    //the actual votes for B in the election
	double rand_val = 0.0;  //random value
	
	//puts margin into an interger
	margin = (margin / 100) * num_votes;
	
	//puts machine error into an integer
	machine_error = machine_error * 100;
	
	//rounds the winner votes up to the nearst integer
	winners_votes = int( ceil( ( num_votes / 2.0 ) + ( margin / 2.0 ) ) );
	
	//rounds loser votes down to the nearest integer
	losers_votes = int( floor( ( num_votes / 2.0 ) - ( margin / 2.0 ) ) );

	
	//runs the election 500 times 
	for (i = 0; i < trials; ++i)
	{
	    //this resets these variables for the next election trial
		j = 0;
		
		votes_for_A = 0;   

		votes_for_B = 0;
		
		for (k = 0; k < winners_votes; ++k)
		{
			
			//calculates a random value to compare with the machine error
			rand_val = (rand() * rand() % 10000);
			
			if (rand_val <= machine_error)
			{
				//adds to canidate B's total
				++votes_for_B;
			}

			else
			{
				//adds to canidate A's total
				++votes_for_A;
			}

		}
		
		for (k = 0; k < losers_votes; ++k)
		{
			//calculates a random value to compare with the machine error
			rand_val = (rand() * rand() % 10000);
			
			if (rand_val <= machine_error)
			{
				//adds to canidate A's total
				++votes_for_A;
			}

			else
			{
				//adds to canidate B's total
				++votes_for_B;
			}

		}

		//stores votes in an array
		votes[i][j] = votes_for_A;
		++j;		
		
		votes[i][j] = votes_for_B;
		
	}
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function will calculate how many elections went the wrong way, meaning
* candidate B won or tied them instead of canidate A winning. It will then 
* calculate the error rate as a percentage of the flipped elections. 
*
* @param[in,out]    votes[][2] - stores the amount of votes that each canidate 
*                                 got with the machine error. 
* @param[in]        trials - the amount of trials we run for a given election.                   
* @param[in,out]    flipped_elections - the amount of elections that canidate B
*                                        won/tied over canidate A.
* @param[in,out]    percent error - the error rate of elections after  
*                                    500 trials
* @returns none                     
*****************************************************************************/
void calc_error( int votes[][2], int trials, int &flipped_elections,
	 double &percent_error )
{
	int i = 0;
	int j = 0;

	//checks to see if the votes for B is greater than or equal to A
	for ( i = 0; i < trials; ++i )
	{
		for ( j = 0; j < 1; ++j )
		{
			if ( votes[i][j] <= votes[i][j + 1] )
			{
				//elections that went the wrong way
				++flipped_elections;
			}
		}
	}
	
	/* calculates the error rate of how many elections went the wrong way
    after 500 trials */
	percent_error = ( flipped_elections * 100.0 ) / trials;

}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Prints the summary of the process and calculates the error percentage. 
*
* @param[in]     num_votes - total number of votes for a given election
* @param[in]     margin - the amount canidate A wins over canidate B 
* @param[in]     machine_error - the error that a given electronic voting 
*                                     machine has. 
* @param[in]     trials - the amount of trials we run for a given election. 
* @param[in]     flipped_elections - the amount of elections that canidate B
*                                      won over canidate A. 
* @param[in]     percent error - the error rate of elections after 500 trials
*                                
* @returns none
*****************************************************************************/
void display_summary( int trials, double num_votes, double margin, 
	double machine_error, int flipped_elections, double percent_error)
{
   //prints summary
	cout << endl << " ** Machine Error Summary ** " << endl << endl
		 << "Number of votes: " << num_votes << endl << "Election margin: "
		 << margin << "% " << endl << "Machine error percentage: " 
		 << machine_error << "%" << endl << endl;

   //prints the amount of trials, false elections, and error rate
	cout << "For " << trials << " runs, " << flipped_elections << " incorrect "
		 << "elections occurred, for an error rate of " << percent_error
		 << "%" << endl;

}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Gets the user choice of whether or not to run another simulation.
*
* @returns choice - user choice to run another simulation. 
*****************************************************************************/
char get_choice( )
{
	char choice = '?';
	
	//asks the user if they want to run another simulation
	do {
		cout << "Run another simulation? (Y/N): ";
		cin >> choice;

		//puts choice into upper case
		choice = toupper(choice);

		if (choice == 'Y')
		{
			cout << endl;
			break;

		}
		
		else if (choice == 'N')
		{
			//ends program 
			return 0;
		}

		else
		{	
			cout << " Invalid choice: must be Y or N. " << endl;
		}

	} while ((choice != 'Y') && (choice != 'N'));
	
  return choice;
}
