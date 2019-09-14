#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include<iostream>
#include<cmath>
#include<string>
#include<map>
#include<algorithm>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<iomanip>
#include<list>
#include<climits>
#include<queue>
#include<iomanip>
#include<functional>

using namespace std;

const int R = 6373;

/**************************************************************************//**
* @class city
*
* @par Description:
* This class will hold all date for a city. The index will hold the numerical
* index used to represent the city through the program. The boolean variable
* visited will represent if we have visited the city yet. The distance will hold
* the total distance traveled to get to this city. prevCity will hold the numerical
* index for the city that will be traveled to before this city. cityName will
* hold the actual name of the city. cityDistance will hold the distance from the
* city to every other city. children will hold the numerical index for every city
* that should be traveled to after this city.
*
******************************************************************************/
class city {
public:
    //Numerical index for city
    int index = 0;
    //If node has been visited
    bool visited = false;
    //Distance in terms of path
    double distance = 900;
    //Previous city's index
    int prevCity;

    //Holds actual name of node
    string cityName;
    //Vector to hold distance to every other city
    vector <double> cityDistance;
    vector <city> children;
    int childCount = 0;

    bool operator< (const city &temp) const
    {
        return (distance > temp.distance);
    }

};

//function prototypes here
double findDistance ( double lon1, double lon2, double lat1, double lat2 );
void readInFile ( ifstream &fin, map<string, vector<double>> &cities );
void bruteForce (map<string, bool> visitCities, map<string, vector<double>> &cities,
                 string city, double d, map<double, list<string>> &circuits, list<string> path,
                 int numCities, string startCity, double &min);
int readInCities (ifstream &fin, map<string, bool>& visitCities, map<string,
                  vector<double>> &cities, map<string, vector<double>> &inputCities);
void printShortestPath (map<double, list<string>> &circuits, double min, string startCity, double time );

int primAlg(int numCities, map<string, vector<double>> inputCities, string startCity);
void createAdjMatrix( map<string, vector <double>> inputCities, vector<city> &cityList);
void createVector( map<string, vector <double>> inputCities, string startCity, vector <city> &cityList);
bool sortFunc (city cityOne, city cityTwo);

#endif
