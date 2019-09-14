/******************************************************************************
* Name: Fagrey, Nathaniel
* ID: 7416949
* Section: M0002
* Homework 6
*****************************************************************************/
#include<iostream>
#include<fstream>
#include<iomanip>
#define _CRT_SECURE_NO_WARNINGS_
using namespace std;

void readData(ifstream &fin, double data[], int size);

int minloc(double data[], int size);

int maxloc(double data[], int size);


int main(int argc, char *argv[])
{
	ifstream fin;
	ofstream fout;

	char inputFile[100] = "";
	char outputFile[100];
	double *data;
	int arrSize;
	int min, max;
	int i;
	int j = 0;
	
	if (argc != 3)
	{
		cout << "Incorrect number of arguments given. " << endl;

		return 1;
	}

	strcpy(inputFile, argv[1]);

	strcpy(outputFile, argv[2]);
	
	fin.open(inputFile);

	if (!fin.is_open())
	{
		cout << "Unable to open input file. " << endl;

		return 1;
	}

    
	fout.open(outputFile);

	if (!fout.is_open())
	{
		cout << "Unable to open output file. " << endl;

		return 1;
	}

	fin >> arrSize;
	
	data = new (nothrow) double[arrSize];
    
	if (data == nullptr)
	{
		cout << "Failed to allocate array. " << endl;

		delete [] data;
		
		return 1;
	}
	
	readData(fin, data, arrSize);
	
	min = minloc(data, arrSize);

	max = maxloc(data, arrSize);
	
	
	cout << "The data set size is " << arrSize << "." << endl <<
		fixed << setprecision(5) << "The smallest data point is " << 
		data[min] << " located at index " << min << "." << endl << 
		"The largest data point is " << data[max] << " located " << 
		"at index " << max << "." << endl;
	
	
	fout << arrSize << endl;
	
	for (i = 0; i < arrSize; ++i)
	{
		fout << fixed << setprecision(5) << data[i] << " ";
		
		++j;
		
		if (j == 5)
		{
			fout << endl;
			
			j = 0;
		}
	}
	
	
	delete [] data;
	
	fin.close();
	fout.close();

    return 0;

}

void readData(ifstream &fin, double data[], int size)
{
	int i = 0;;

	while (i < size)
	{
		fin >> data[i];
		
		++i;
     
	}
}

int minloc(double data[], int size)
{
	int i = 0;
	double min = 0;
	int lowestIndex = 0;
	
	min = data[0];
	
	for (i = 0; i < size; ++i)
	{
		if (data[i] < min)
		{
			min = data[i];
		    lowestIndex = i;
		
		}
	}

	return lowestIndex;
}

int maxloc(double data[], int size)
{
	int i = 0;
	double max = 0;
	int largestIndex = 0;
	max = data[0];

	for (i = 0; i < size; ++i)
	{
		if (data[i] > max)
		{
			max = data[i];
			largestIndex = i;
		}
	}
   
	return largestIndex;
}