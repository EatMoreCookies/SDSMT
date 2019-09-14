/******************************************************************************
* Name: Fagrey, Nathaniel
* ID: 7416949
* Section: M0002
* Homework 9a
*****************************************************************************/
#include <iostream>
#include <iomanip>

#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"

using namespace std;

int volume( int height, int baseSU );

int main(int argc, char **argv)
{
    int base1, base2;
    int height1, height2;
    int volume1, volume2;
    int remaining;
    int result = Catch::Session().run( argc, argv );

    if( result )
    {
        cout << "Failed to pass test cases" << endl;
        return 0;
    }

	
	// get the data for both boxes
    cout <<"Enter the larger box data" << endl;
    cout <<"Enter the area of the base: ";
    cin >> base1;
    cout << "Enter the height: ";
    cin >> height1;
    cout << endl << endl <<"Enter the smaller box data" << endl;
    cout <<"Enter the area of the base: ";
    cin >> base2;
    cout << "Enter the height: ";
    cin >> height2;

    //my code
	volume1 = volume(height1, base1);

	volume2 = volume(height2, base2);

	remaining = volume1 - volume2;


    // End of my code
    cout << "The small box would displace all but " << remaining
         << " cubic units of the larger box." << endl;
    
    return 0;
}


int volume(int height, int baseSU)
{
	int sum;
	
	if (baseSU == 0)
	return 0;


	sum = volume(height, baseSU - 1);

	return sum += height; 
}


TEST_CASE( "VOLUME" )
{
    CHECK( volume( 0, 34 ) == 0 );
    CHECK( volume( 24, 0 ) == 0 );
    CHECK( volume( 8, 30 ) == 240 );
    CHECK( volume( 1, 10 ) == 10 );
    CHECK( volume( 3, 19 ) == 57 );

	//to see if it can handle large numbers.
	CHECK( volume( 999, 999 ) == 998001 );

	//to see if it right away passes the base case. 
	CHECK( volume( 10, 1 ) == 10 );

	//to see if it will still return 0 even though is fails the base case
	CHECK( volume( 0, 0 ) == 0 );

	//checking a really big number with a small number. 
	CHECK(volume(999, 1) == 999);

	//to see if it can handle weird formats
	CHECK(volume(701 - 5, (8 * 2) + 1) == 11832);

}

