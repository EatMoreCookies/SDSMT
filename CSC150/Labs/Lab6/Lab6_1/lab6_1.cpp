

#include<iostream>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<iomanip>
using namespace std;

int caloriesEvery5min = 0.0;
int timeMinutes = 0;
double caloriesBurned = 0;
const double caloriesPerMin = 3.9;

int main(){
	cout << "Enter the amount of time run: ";
	cin >> timeMinutes; 


	int i = 5;
	while (i < timeMinutes ){
      
		caloriesBurned = caloriesPerMin * i;
		cout << fixed << setprecision(2);
		cout << left << setw(10) << i << caloriesBurned << endl;
		
		i = i + 5;
			
	}

	return 0; 

}