/******************************************************************************
* Name: Fagrey, Nathaniel
* ID: 7416949
* Section: M0002
* Homework 8
*****************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<iomanip>

using namespace std;


int main(int argc, char **argv)
{
	vector<int> data;
	ifstream fin;
	ofstream fout;
	int count = 0;
	int num = 0;
	vector<int>::iterator itr, spot;
	vector<int>::reverse_iterator ritr;
	int uniqueVals = 0;
	int i, j;
	long long int sum;
	double average = 0.0;


	if (argc < 4 || argc > 4)
	{
		cout << "Incorrect number of arguments entered. " << endl;

		return -1;
	}

	fin.open(argv[1]);

	if (!fin.is_open())
	{
		cout << "Unable to open input file. " << endl;

		return -1;
	}

	
	while (fin >> num)
	{
		data.push_back(num);
	}
	

	fout.open(argv[3]);

	if (!fout.is_open())
	{
		cout << "Unable to open output files. " << endl;

		return -1;
	}

	fout << "Original data set size: " << data.size() << endl;

	sort(data.rbegin(), data.rend());

	spot = unique(data.begin(), data.end());

	for (itr = data.begin(); itr != spot; ++itr)
	{
		++uniqueVals;
	}

	
	
	fout << "Number of unique values: " << uniqueVals << endl;

	fout << "Five largest values: ";

	i = 0;
	for (itr = data.begin(); i < 5; ++itr)
	{
		fout << *itr << " ";

		++i;
	}

	
	
	fout << endl << "Five smallest values: ";

	data.resize(uniqueVals);
	
	i = 0;
	for (ritr = data.rbegin(); i < 5; ++ritr)
	{
		fout << *ritr << " ";

		++i;
	}
	
	
	sum = accumulate(data.begin(), data.end(), 0);

	fout << endl << "Sum of unique values: " << sum << endl;
	
	average = double(sum) / uniqueVals;

	fout << "Average of unique values: " << fixed << setprecision(4) 
		<< average << endl;

	
	fout.close();
	
	fout.open(argv[2]);

	if (!fout.is_open())
	{
		cout << "Unable to open output file. " << endl;
		
		return -1;
	}
	
	j = 0;
	for (i = 0; i < uniqueVals; ++i)
	{
		fout << data.at(i) << " ";
		
		++j;
		
		if (j == 5)
		{
			fout << endl;

			j = 0;
		}
    }

	
	
	fin.close();
	fout.close();
	
	return 0;
}