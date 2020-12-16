/*************************************************************************//**
* @file
*
* @mainpage Program 2 - Approximation
*
* @section course_section Course Information
*
* @author Nathaniel Fagrey
*
* @date October 10, 2017
*
* @par Professor:
*         Professor Kelly Corwin
*
* @par Course:
*         CSC 150 - Section 3 -  3:00 PM
*
* @par Location:
*         Engineering and Physics Building - Room 253
*
* @section program_section Program Information
*
* @details This program allows a user to approximates e^x, sin(x), and cos(x)
*          with the x value that they so choose. To do this, the program uses
*          the Taylor series to approximate.
*
*         The Taylor series is a way to approximate a value using an "infinite
*         sum of terms." If the values we want to calculate are relvatively 
*		  close to zero, then we use what is called a Maclaurin series which is  
*		  a type of Taylor series. 
*
*         The Maclaurin series uses terms defined as follows: 
*         ( x^i ) / i!. X is the value to be approximated, i is equal to the 
*         number of the term we are on ( for example: the next term would be 
*         ( x ^ (i+1) ) / (i+1)!. i! is the factorial of i which is equal to 
*         the sum of all the postive integers before i and including i. The 
*         terms are then added together (in case of sin(x) and cos(x), they are
*         subtracted every other one) until the number of terms that the user 
*         chooses is met. For sin(x) and cos(x) i increases by 2 for each term. 
*
*         The program will then print these approximations along with the 
*         approximations calculated with the C math library. 
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      No special compiling instructions.
*
* @par Usage:
@verbatim
C:\Users\7416949\Documents\SDSMT\Fall 2017\CSC150\Programs\prog2
  \Prog2\prog2.cpp
*
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug when a value for the number of terms is entered that is 10 characters
  or more, the function goes into an infinite loop.
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Septmeber 19, 2017  Started the project.
September 28, 2017  Started to define key functions.
October 2, 2017 All three approximation options were set up.
October 3, 2017 All three funtions up and running correctly.
*****************************************************************************/


#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;



//Checks the validity of the menu choice
int Get_Menu_Choice(int menu_choice);

//Makes sure x is a valid input for e^x
double Get_X_For_E(double x_input_e);

//Checks to make sure the number of terms entered is correct
int Get_Num_Terms(int num_terms);

//Calculates the factorials for all three functions
long double Factorial(int input);

//Approximates e^x
double My_EX(double x, int numTerms);

//Makes sure the values for x entered by the user are in the allowed domain
double Get_Degrees(double x_input);

//Converts the user inputed x from degrees into radians
double Convert_To_Radians(double degrees);

//Approximates sin(x)
double My_SinX(double x, int num_terms);

//Approximates cos(x)
double My_CosX(double x, int num_terms);

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function outputs a description of the process it will do. Then it asks
* for user inputs for the type of math function they would like to approximate.
* The user then inputs the value to approximate; as well as, the number of terms
* to use. After approximating, the function outputs the value of the 
* approximation; as well, as the value that the computer gets with the c math 
* library function.
*
* @returns 0 program ran successful.
*****************************************************************************/

int main()
{
	int menu_choice = 0;         //user menu choice 
	double x_input_e = 0.0;      //x input for e^x
	int num_terms = 0;          //number of terms to use 
	double approx_e = 0.0;      //approximation of e^x
	double cmath_e = 0.0;       //the value of e^x from c math library
	double x_input_trig = 0.0;  //x input for sin and cos approximations
	double x_in_radians = 0.0;  //x in radians after being converted 
	double approx_sin = 0.0;   //approximation of sin(x)
	double cmath_sin = 0.0;    //the value of sin(x) from c math library
	double approx_cos = 0.0;   //approximation of cos(x)
	double cmath_cos = 0.0;    //the value of cos(x) from c math library

	
	//Description of the process
	cout << "This program will allow you to choose a mathematical function to "
		 << endl << "approximate using the Taylor series. You will then be "
		 << endl << "able choose the number of terms to use which will affect "
		 << endl << "the accuracy of the apporoximation. Then, the program "
		 << endl << "will perform the approximation and compare the results "
		 << endl << "with the corresponding function from the C Math library. "
		 << endl << endl;

	do
	{   
		//Prints menu
		cout << "Menu" << endl << "1. Approximate e^x. " << endl
			<< "2. Approximate sin(x). " << endl << "3. Approximate cos(x). "
			<< endl << "4. Quit Program." << endl << endl << "Enter Choice: ";
		    
		    //user's menu choice
		    cin >> menu_choice;
        
	    //Calls the function Get_Menu_Choice
		menu_choice = Get_Menu_Choice( menu_choice );


		switch ( menu_choice )
		{

			case 1:
				
				//Asks for an x value for e^x
				cout << endl << "Enter a value for x between 0 and 5: ";
					
				    cin >> x_input_e;
                
				//Calls the function Get_X_For_E
				x_input_e = Get_X_For_E( x_input_e );

				
				//Asks for number of terms to use
				cout << "Enter the number of terms you want to use: ";
					
				    cin >> num_terms;
                
                //Calls the function Get_Num_Terms
				num_terms = Get_Num_Terms( num_terms );

				
				//Calls function My_EX to approximate e^x
				approx_e = My_EX(x_input_e, num_terms);

				
				cout << endl << fixed << setprecision(8) 
					 << "Approximation with series: " << approx_e << endl;

				
				//Calculates e^x using the c math library
				cmath_e = pow( M_E, x_input_e );

				
				cout << fixed << setprecision(8)
					 << "Approximation with cmath function: " << cmath_e
					 << endl;

				break;


			case 2:

				//Asks for an x value between -180 and 180 degrees
				cout << endl << "Enter a value for x in degrees: ";
					
				    //User input in degrees
				    cin >> x_input_trig;

				//Calls function Get_Degrees
				x_input_trig = Get_Degrees( x_input_trig );

				//Calls function Convert_To_Radians
				x_in_radians = Convert_To_Radians( x_input_trig );


				//Asks for number of terms
				cout << "Enter the number of terms you want to use: ";
					
				     cin >> num_terms;

				//Calls function Get_Num_Terms
				num_terms = Get_Num_Terms( num_terms );


				//Calls function My_SinX to approximate sin(x)
				approx_sin = My_SinX( x_in_radians, num_terms );

				cout << endl << fixed << setprecision(8)
					 << "Approximation with series: " << approx_sin << endl;


				//Calculates sin(x) using c math library
				cmath_sin = sin( x_in_radians );

				cout << fixed << setprecision(8)
					 << "Approximation with cmath function: " << cmath_sin
					 << endl;
				break;

			
			case 3:
				
				//Asks for a value for x between -180 and 180 degrees
				cout << endl << "Enter a value for x in degrees: ";
					
				    //User input in degrees
				    cin >> x_input_trig;

				
				//Calls function x_input_trig
				x_input_trig = Get_Degrees( x_input_trig );

				//Calls function Convert_To_Radians to convert x
				x_in_radians = Convert_To_Radians( x_input_trig );


				//Asks for number of terms
				cout << "Enter the number of terms you want to use: ";
					
				    cin >> num_terms;

				//Calls function Get_Num_Terms
				num_terms = Get_Num_Terms( num_terms );


				//Calls function My_CosX to approximate cos(x)
				approx_cos = My_CosX( x_in_radians, num_terms );

				
				cout << endl << fixed << setprecision(8)
					<< "Approximation with series : " << approx_cos << endl;

				//Calculates cos(x) using the c math library 
				cmath_cos = cos( x_in_radians );

				cout << fixed << setprecision(8)
					 << "Approximation with cmath function: " << cmath_cos
					 << endl;

				break;
           
		    //This case ends the program. 
			case 4:

				return 0;

				break;

		}
		
		//Adds a new line to seperate the new menu that might be printed
		cout << endl;
	
	//Keeps printing the menu until the user selects quit
	} while ( menu_choice != 4 );

	return 0;
}



/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Makes sure that the menu choice that the user inputed is a valid choice.
* If not valid the program will print an error message and re-print the menu.
* The function then returns the first valid menu choice.
*
* @param[in]  menu_choice - The menu choice inputed by the user.
*
* @returns menu_choice - The menu choice inputed by the user.
*****************************************************************************/

int Get_Menu_Choice( int menu_choice )
{   
	//Keeps printing menu until a valid choice is inputed 
	while ( ( menu_choice < 1 ) || ( menu_choice > 4 ) )
	{
		cout << "Error: invalid menu choice. " << endl << endl << "Menu" << endl
			 << "1. Approximate e^x. " << endl << "2. Approximate sin(x). " <<
			 endl << "3. Approximate cos(x). "
			 << endl << "4. Quit Program." << endl << endl << "Enter Choice: ";
		
		    cin >> menu_choice;
	}
	return menu_choice;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Makes sure that the value inputed for x is between 0 and 5.
*
* @param[in]  x_input_e - User choice for x in the approximation e^x.
*
* @returns x_input_e - User choice for x in the approximation e^x.
*****************************************************************************/

double Get_X_For_E( double x_input_e )
{   
	//Keeps printing until a value for x between 0 and 5 is entered
    while ( ( x_input_e < 0 ) || ( x_input_e > 5 ) )
	{
		cout << "Invalid input: x must between 0 and 5. " << endl << endl
			 << "Enter a value for x between 0 and 5: ";
		    
		    cin >> x_input_e;
	}
	return x_input_e;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Makes sure the number terms needed for the approximations is
* between 1 and 20
*
* @param[in]  num_terms - user input for the number of terms.
*
* @returns num_terms - user input for the number of terms.
*****************************************************************************/

int Get_Num_Terms( int num_terms )
{   
	//Keeps printing until the user enters the correct number of terms
    while ( ( num_terms < 1 ) || ( num_terms > 20 ) )
	{
		cout << "Invalid input: number of terms must be between 1 and 20. "
			<< endl << endl << "Enter the number of terms you want to use: ";
		
		    cin >> num_terms;

	}
	return num_terms;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Calculates the factorials for the approximations.
*
* @param[in]      input - The number the user wants to create a factorial for.
*  
* returns product - The factoral that was calculated with the input. 
*****************************************************************************/

long double Factorial( int input )
{	
	//The calculated factorial
	double product = 1;
	int j = 0;

	//Calculates the factorial for a given number
	for ( j = input; j > 0; j-- )
	{
		product = product * j;
    }
	
	return product;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Calculates e^x using Taylor series. 

* @param[in]      x - The value that is to be approximated
* @param[in]      num_terms - The amount of terms in the Taylor series 
*                             that the function will use to approximate. 
*
* returns approx_e - The approximation of e^x using Taylor series. 
*****************************************************************************/

double My_EX( double x, int numTerms )
{    
	//Approximation e^x
	double approx_e = 0.0; 
	int i = 0;  
	
	//Approximates e^x using Taylor Series
	while ( i < numTerms )
	{
		approx_e = approx_e + pow( x, i ) / Factorial( i );
		++i;
	}
	return approx_e;

}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Makes sure the value entered in degrees for x is between -180 and 180 degrees.
* 
* @param[in]  x_input - The x value in in degrees inputed by the user. 

* returns x_input - The x value in in degrees inputed by the user. 
*****************************************************************************/

double Get_Degrees( double x_input ){
	
	//Prints as long as an invalid input for x is inputed 
	while ( ( x_input < -180 ) || ( x_input > 180 ) )
	{
		cout << "Invalid Input: Input must be between -180 and 180 degrees. " 
			 << endl << endl << "Enter a value for x in degrees between -180 " 
			 " and 180 degrees: ";
		    
		    //User input
		    cin >> x_input;
	}
	return x_input;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Converts x from degrees into radians.
*
* @param[in]      degrees - The value of x inputed by user. 
* 
* @returns x_in_radians - x in radians after being converted from degrees
*****************************************************************************/

double Convert_To_Radians( double degrees ){
	
	//x after being converted to radians
	double x_in_radians = 0.0; 
	
	    //Converts x from degrees into radians
	    x_in_radians = ( M_PI * degrees ) / 180.0;

	return x_in_radians;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Approximates sin(x) using Taylor series
* 
* @param[in]      x - The value for x inputed by the user converted to degrees
* @param[in]      num_terms - The number of terms to use to approximate sin(x)
*                              using the Taylor Series.  
*
* @returns approx_sin - The approximation of sin(x) using Taylor series. 
*****************************************************************************/

double My_SinX( double x, int num_terms ){
	
	//Approximation of sin(x)
	double approx_sin = 0.0; 
	int i = 1;
	int j = 1;

	//Approximates sin(x) using Taylor series
	while ( i <= num_terms * 2 )
	{
		approx_sin = approx_sin + j * ( pow( x, i ) / Factorial( i ) );
		
		i = i + 2;
		j = -1 * j;
	}
	return approx_sin;
}

/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Approximates cos(x) using the Taylor series
* 
* @param[in]       x  - The value inputed by the user in degrees converted to
*                       radians. 
* @param[in]     num_terms - The number of terms used to approximate x using
                             Taylor series. 
*
* @returns approx_cos - The approximation of cos(x) using Taylor series
*****************************************************************************/

double My_CosX( double x, int num_terms )
{    
	//Approximation of cos(x)
	double approx_cos = 0.0;
	int i = 0;
	int j = 1;

	//Approximates cos(x) using Taylor series
	while (i < num_terms * 2){
		
		approx_cos = approx_cos + j * ( pow( x, i ) / Factorial( i ) );
		
		i = i + 2;
		j = -1 * j;
	}
	return approx_cos;
}
