#include<iostream>
#include<cmath>
#include<iomanip>
#include<cctype>

using namespace std;


double startVal = 0.0;
int numTerms = 0;
double root = 0;
double rootVals = 0.0;
char userchoice = '?';
int main()
{   
	do {
		cout << "Enter the starting Value: ";
		cin >> startVal;

		cout << "Enter the root: ";
		cin >> root;

		cout << "How many terms: ";
		cin >> numTerms;

		cout << "Starting Value: " << fixed << setprecision(8) << startVal << endl;
		int i = 0;
		for (i = 0; i < numTerms; ++i){
			
			
			startVal = pow(startVal, (1 / root));
			cout << fixed << setprecision(8);
			cout << startVal << "     ";
			int j = 0;
			j = j + 1;
			if (j == 5){
				cout << endl; 
			}
		}
			cout << "Do you want to continue? (Y/N) ";
			cin >> userchoice;
			
			userchoice = toupper(userchoice);
		

	} while (userchoice == 'Y');
	
	return 0;
}