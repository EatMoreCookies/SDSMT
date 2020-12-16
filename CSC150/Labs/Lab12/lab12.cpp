//lab 12 - Geometric figures from file
//Fall 2017

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*Complete function prototype for read_data*/
double read_data(ifstream &input, int data[][2]);


double triangle(int a);
double square(int a);
double pentagon(int a);
double hexagon(int a);

int main()
{
	int data[50][2] = { 0, 0 };
	char out_filename[50];
	char in_filename[50];
	ifstream input;
	ofstream output;
	int num_read_vals;
	int i = 0;
	int length = 0;
	double area = 0.0;
	double total_area = 0.0;
	
	
	
	
	//Ask the user to enter the name of the input file and the name of the output file, storing to the two cStrings.
	cout << "Enter input file name: ";
	cin.getline(in_filename, 50);

	cout << endl << "Enter output filename: ";
	cin.getline(out_filename, 50);


	// Open the named input data file, if error occurs, display message and exit the program.
	input.open(in_filename);

	if (!input.is_open())
	{
		cout << "Error: unable to open file" << endl;

		return -1;
	}



	// Pass opened file variable and the array to read_data function.
	num_read_vals = read_data(input, data);



	// Read through each row of valid data in the array, 
	//		passing length value to correct function to calculate area.
	//		Add the returned value from the math function to the total area.

	for (i = 0; i < num_read_vals; ++i)
	{
		
		if (data[i][0] == 3)
		{
			length = data[i][1];
			area = triangle(length);
		}
	
		else if (data[i][0] == 4)
		{
			length = data[i][1];
			area = square(length);
		}
    
		else if (data[i][0] == 5)
		{
			length = data[i][1];
			area = pentagon(length);
		}
	
		else if (data[i][0] == 6)
		{
			length = data[i][1];
			area = hexagon(length);
		    
		}
		
		cout << area << endl;
		
		total_area = area + total_area;
	} 
	


	// When all data processed, open named output file.
	//  If error occurs, display message and exit. Otherwise, write total area to file.
	output.open(out_filename);

	if (!output.is_open())
	{
		cout << "Error: file failed to open. " << endl;
		return -1;
	}

	output << total_area;

	// Close all files when finished using them.

	input.close();
	
	output.close();

	return 0;
}

// Function receives the opened file variable and the 2D data array.
// In this function, read the entire data file, storing all values to the 2D integer array; 
//   return the number of figures(rows) read in.
double read_data(ifstream &input, int data[][2])
{
	int i = 0;
	int j = 0;
	int num_read_vals = 0;
	
	while (input >> data[i][0] >> data[i][1])
	{
		
		
		++num_read_vals;
		++i;
	}
	
	return num_read_vals;
}

double triangle(int a)
{
	return sqrt(3) / 4.0 * pow(a, 2);
}

double square(int a)
{
	return a * a;
}

double pentagon(int a)
{
	return 1 / 4.0 * sqrt(5 * (5 + 2 * sqrt(5))) * pow(a, 2);
}

double hexagon(int a)
{
	return 3 * sqrt(3) / 2 * pow(a, 2);
}