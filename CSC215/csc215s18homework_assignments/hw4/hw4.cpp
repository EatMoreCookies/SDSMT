/******************************************************************************
* Name: Fagrey, Nathaniel
* ID: 7416949
* Section: M0002
* Homework 4
*****************************************************************************/

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int num = 0;
	double sum = 0;
	double average = 0.0;
	int min = numeric_limits<int>::max();
	int max = numeric_limits<int>::min();
	int count = 0;
	
	cout << "Enter ^z to end program. " << endl;
	

	cout << "Enter an integer: ";
	
	while (cin >> num)
	{
		++count;
		
		cout << "Count: " << count << endl;
		
		//checks for min
		if (num < min)
		{
			min = num;
		}
	
		cout << "Minimum: " << min;

		//checks for max
		if (num > max)
		{
			max = num;
		}
	
		cout << "   Maximum: " << max << endl;
	
		//sums
		sum += num;

		cout << "Sum: " << fixed << setprecision(4) << sum;
		
		//averages
		average = sum / count;

		cout << "   Average: " <<  average << endl;
	
		cout << endl << "Enter an integer: ";
	}

	return 0;
}