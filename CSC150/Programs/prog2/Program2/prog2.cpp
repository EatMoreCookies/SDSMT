/*************************************************************************//**
* @file
*
* @mainpage Program 2 - Approximation
*
* @section course_section Course Information
*
* @author Nathaniel Fagrey
*
* @date October 6, 2017
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
* @details <This should be a very detailed writeup of what the program does>
*
* <A blank line starts a new paragraph so this is paragraph 2>
*
* <This would be paragraph 3>
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      No special compiling instructions.
*
* @par Usage:
@verbatim
C:\Users\7416949\Documents\SDSMT\Fall 2017\CSC150\Programs\prog2
* \Program2\prog2.cpp
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug when a value for the number of terms is entered that is 10 characters
*      or more, the function goes into an infinite loop. 
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

//Makes sure a valid input for x for e^x
double Get_X_For_E(double x_input_e);

//Checks to make sure the number of terms entered is correct
int Get_Num_Terms(int num_terms);

//calculates the factorials for all three functions
long double Factorial(int input);

//Approximates e^x
double My_EX(double x, int numTerms);

//Makes sure the values entered by the user are in the allowed domain
double Get_Degrees(double x_input);

//converts the user inputed x in degrees into radians
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
* for user inputs for the type of math function it would like to approximate. 
* The user then inputs the value to approximate as well as the number of terms
* to use. After approximating, the function outputs the valued of the 
* as well as the value that the computer gets with the cmath library function.
* 
* @returns 0 program ran successful.
*****************************************************************************/
int main()
{
    int menu_choice = 0;
    double x_input = 0.0;
    int num_terms = 0;
    double x_input_e = 0.0;
    double approx_e = 0.0;
    double x_input_trig = 0.0;
    double x_in_radians = 0.0;
    double approx_sin = 0.0;
    double approx_cos = 0.0;
    double cmath_e = 0.0;
    double cmath_sin = 0.0;
    double cmath_cos = 0.0;

	cout << "This program will allow you to choose a mathematical function to "
		<< endl << "to approximate using the Taylor series.You will then be "
		<< endl << "able choose the number of terms to use which will affect "
		<< endl << "the accuracy of the apporoximation.Then, the program will "
		<< endl << "perform the approximation and compare the results with "
		<< endl << " the corresponding function from the C Math library. "
		<< endl << endl;
	
	do 
	{
		cout << "Menu" << endl << "1. Approximate e^x. " << endl
		<< "2. Approximate sin(x). " << endl << "3. Approximate cos(x). "
		<< endl << "4. Quit Program." << endl << endl << "Enter Choice: ";
	       
			cin >> menu_choice;

		menu_choice = Get_Menu_Choice(menu_choice);


		switch (menu_choice)
		{
		
		    case 1:
				cout << endl << "Enter a value for x between 0 and 5: ";
			        cin >> x_input_e;

			    x_input_e = Get_X_For_E(x_input_e);

			    
				cout << "Enter the number of terms you want to use: ";
			        cin >> num_terms;

			    num_terms = Get_Num_Terms(num_terms);

			    
				approx_e = My_EX(x_input_e, num_terms);

			    cout << fixed << setprecision(8) 
			         << "Approximation with series: " << approx_e << endl;
			
				
				cmath_e = pow(M_E, x_input_e);

			    cout << fixed << setprecision(8) 
				     << "Approximation with cmath function: " << cmath_e 
					 << endl;
			
				break;


            case 2:
			    
				cout << endl << "Enter a value for x in degrees: ";
			        cin >> x_input_trig;

			    x_input_trig = Get_Degrees(x_input_trig);

			    x_in_radians = Convert_To_Radians(x_input_trig);

                
				cout << "Enter the number of terms you want to use: ";
			        cin >> num_terms;

			    num_terms = Get_Num_Terms(num_terms);

			    
				approx_sin = My_SinX(x_in_radians, num_terms);

			    cout << fixed << setprecision(8) 
					 << "Approximation with series : " << approx_sin << endl;

			    
				cmath_sin = sin(x_in_radians);

			    cout << fixed << setprecision(8) 
					<< "Approximation with cmath function: " << cmath_sin 
					<< endl;
			break;

			case 3:
		        cout << endl << "Enter a value for x in degrees: ";
					cin >> x_input_trig;

				x_input_trig = Get_Degrees(x_input_trig);

				x_in_radians = Convert_To_Radians(x_input_trig);


				cout << "Enter the number of terms you want to use: ";
				    cin >> num_terms;

				num_terms = Get_Num_Terms(num_terms);

				
				approx_cos = My_CosX(x_in_radians, num_terms);

				cout << fixed << setprecision(8) 
					<< "Approximation with series : " << approx_cos << endl;
				
				
				cmath_cos = cos(x_in_radians);

				cout << fixed << setprecision(8) 
			         << "Approximation with cmath function: " << cmath_cos
					 << endl;
			
				break;

			case 4:
			
			    return 0;
			
			break;

		}
	
	} while (menu_choice != 4);
		
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
* @param[in,out]  menu_choice - The menu choice inputed by the user. 
*
* @returns menu_choice
*****************************************************************************/

int Get_Menu_Choice(int menu_choice)
{
	while ((menu_choice < 1) || (menu_choice > 4))
	{
		cout << "Error invalid Menu choice. " << endl << "Menu" << endl 
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
* @param[in,out]  x_input_e - User choice for x in the approximation e^x.
*
* @returns x_input_e 
*****************************************************************************/

double Get_X_For_E(double x_input_e)
{

    while ((x_input_e < 0) || (x_input_e > 5))
	{
		cout << "Invalid input: x must between 0 and 5. " << endl
			<< "Enter a value for x between 0 and 5: ";
		cin >> x_input_e;
	}
	return x_input_e;
}
/**************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* Makes sure the number terms needed for all three approximations is 
* between 1 and 20 
* 
* @param[in,out]  num_terms - user input for the number of terms. 
*
* @returns num_terms
*****************************************************************************/
int Get_Num_Terms(int num_terms)
{
	
	while ((num_terms < 1) || (num_terms > 20))
	{
		cout << "Invalid input: number of terms must be between 1 and 20. " << endl
			<< "Enter the number of terms you want to use: ";
		cin >> num_terms;

	}
	return num_terms;
}
/**************************************************************************//**
* @author <Firstname Lastname>
*
* @par Description:
* Calculates the Factorials for all three approximations. 
*
* @param[in]      var1 - a description of variable one, must match name exactly
* @param[out]     var2 - a description of variable two
* @param[in,out]  var3 - a description of variable three
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
* @return  2 a different error occured.
*
*****************************************************************************/
long double Factorial(int input){
	double product = 1;
	int j = 0;

	for (j = input; j > 0; j--){
		product = product * j;

	}
	return product;
}
/**************************************************************************//**
* @author <Firstname Lastname>
*
* @par Description:
* Approximates e^x.
* @param[in]      var1 - a description of variable one, must match name exactly
* @param[out]     var2 - a description of variable two
* @param[in,out]  var3 - a description of variable three
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
* @return  2 a different error occured.
*
*****************************************************************************/
double My_EX(double x, int numTerms){
	double approx_e = 0.0;
	int i = 0;
	while (i < numTerms){
		approx_e = approx_e + pow(x, i) / Factorial(i);
		++i;
	}
	return approx_e;

}
/**************************************************************************//**
* @author <Firstname Lastname>
*
* @par Description:
* Gets x in degrees for sin and cos.
* @param[in]      var1 - a description of variable one, must match name exactly
* @param[out]     var2 - a description of variable two
* @param[in,out]  var3 - a description of variable three
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
* @return  2 a different error occured.
*
*****************************************************************************/
double Get_Degrees(double x_input){
	while ((x_input < -180) || (x_input > 180))
	{
		cout << "Invalid Input: Input must be between -180 and 180 degrees. " << endl
			<< "Enter a value for x in degrees between - 180 and 180 degrees: ";
		cin >> x_input;
	}
	return x_input;
}
/**************************************************************************//**
* @author <Firstname Lastname>
*
* @par Description:
* converts x from degrees into radians. 
* @param[in]      var1 - a description of variable one, must match name exactly
* @param[out]     var2 - a description of variable two
* @param[in,out]  var3 - a description of variable three
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
* @return  2 a different error occured.
*
*****************************************************************************/
double Convert_To_Radians(double degrees){
	double x_in_radians = 0.0;
	x_in_radians = (M_PI * degrees) / 180.0;

	return x_in_radians;
}

/**************************************************************************//**
* @author <Firstname Lastname>
*
* @par Description:
* Approximates sin(x)
* @param[in]      var1 - a description of variable one, must match name exactly
* @param[out]     var2 - a description of variable two
* @param[in,out]  var3 - a description of variable three
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
* @return  2 a different error occured.
*
*****************************************************************************/
double My_SinX(double x, int num_terms){
	double approx_sin = 0.0;
	int i = 1;
	int j = 1;

	while (i <= num_terms * 2){
		approx_sin = approx_sin + j * (pow(x, i) / Factorial(i));
		i = i + 2;
		j = -1 * j;
	}
	return approx_sin;
}


/**************************************************************************//**
* @author <Firstname Lastname>
*
* @par Description:
* Approximates cos(x)
* @param[in]      var1 - a description of variable one, must match name exactly
* @param[out]     var2 - a description of variable two
* @param[in,out]  var3 - a description of variable three
*
* @returns 0 program ran successful.
* @returns 1 the program fail or there was an error.
* @return  2 a different error occured.
*
*****************************************************************************/
double My_CosX(double x, int num_terms){
	double approx_cos = 0.0;
	int i = 0;
	int j = 1;

	while (i < num_terms * 2){
		approx_cos = approx_cos + (j)* (pow(x, i) / Factorial(i));
		i = i + 2;
		j = -1 * j;
	}
	return approx_cos;
}
