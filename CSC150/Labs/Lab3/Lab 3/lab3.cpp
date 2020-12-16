#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int numPeople = 0;
double totalMoney = 0.0;
double donutCost = 0.0;
int wholeDonuts = 0;
int donutsPerPerson = 0;
double moneyLeftover = 0.0;
int leftoverDonuts = 0;

int main()
{

//ask for the number of people.
	cout << "How many people are there? ";
	    cin >> numPeople;

//ask for the total amount of money
	cout << "How much money is there? ";
	    cin >> totalMoney;

//ask for the cost of a single donut 
	cout << "What is the cost of a single donut? ";
		cin >> donutCost;

//now calculate the amount of whole donuts
	wholeDonuts = int(totalMoney / donutCost);

//calculate the amount of donuts that each person gets
	donutsPerPerson = int( wholeDonuts / numPeople );

//calculate the amount of money leftover
	moneyLeftover = totalMoney - (wholeDonuts * donutCost);

//calculate the amount of donuts leftover
	leftoverDonuts = wholeDonuts - (numPeople * donutsPerPerson);

/*print the amount of money left over, the amount of donuts bought, 
the amount of whole donuts leftover, and how many whole donuts per person*/


	cout << wholeDonuts << " donuts were bought. " << endl;
	cout << "The amount of money leftover: " << moneyLeftover << endl;
	cout << "The amount of donuts leftover: " << leftoverDonuts << endl;
	cout << "Each person gets " << donutsPerPerson << " donuts." << endl;


return 0;



}