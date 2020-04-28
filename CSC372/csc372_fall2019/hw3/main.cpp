/*
    Nathaniel Fagrey. CSC372. HW3
*/

#include<iostream>
#include<fstream>
#include "Polygon.h"
using namespace std;



int main( int argc, char * argv[] )
{
    int numPoints;
    int counter = 0;
    ifstream fin;
    vector< Point > allPoints; 
    Point point;

    if (argc == 2)
    {
        fin.open( argv[1] );
    
        if( !fin.is_open() )
        {
            cout << "File failed to open!" << endl;
            return -1;
        }
    }

    fin >> numPoints;
    
    while( numPoints >= 3 )
    {
        counter++;
        allPoints.clear();

        for ( int i = 0; i < numPoints; ++i )
        {
            fin >> point.x >> point.y;
            allPoints.push_back( point );
        }

        Polygon p( allPoints );
        p.operation(counter);

        fin >> numPoints;
    }
    
    

    fin.close();

    return 0;
}