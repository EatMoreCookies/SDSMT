#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main()
{
	int radiusInput = 0;
	double perimInches = 0.0;
	double perimCentimeters = 0.0;
	double areaInches = 0.0;
	double areaCentimeters = 0.0;
	double surfaceAreaIn = 0.0;
	double surfaceAreaCent = 0.0;
	double volumeInches = 0.0;
	double volumeCent = 0.0; 


	cout << "Enter the radius as a whole number: ";
	    cin >> radiusInput;

		radiusInput = abs(radiusInput);

	perimInches = 2 * M_PI * (radiusInput);
	
	perimCentimeters = perimInches * (2.54);

	cout << fixed << showpoint << setprecision(3);
	cout << "The perimeter is " << perimInches << " in " << "and " 
		 << perimCentimeters << " cm" << endl;


	areaInches = M_PI * pow(radiusInput, 2);

	areaCentimeters = areaInches * pow(2.54, 2);
	
	cout << fixed << showpoint << setprecision(3);
	cout << "The area is " << areaInches << " in^2" << " and "
		<< areaCentimeters << " cm^2" << endl;


	
	surfaceAreaIn = 4 * M_PI * pow(radiusInput, 2);

	surfaceAreaCent = surfaceAreaIn * pow(2.54, 2);
	
	cout << fixed << showpoint << setprecision(3);
	cout << "The surface area is " << surfaceAreaIn << " in^2 " << " and "
		<< surfaceAreaCent << " cm^2" << endl;

	
	
	volumeInches = (double(4) / double(3)) * M_PI * pow(radiusInput, 3);

	volumeCent = volumeInches * pow(2.54, 3);

	cout << fixed << showpoint << setprecision(3);
	cout << "The volume is " << volumeInches << " in^3" << " and "
		<< volumeCent << " cm^3" << endl;


	return 0;


}
