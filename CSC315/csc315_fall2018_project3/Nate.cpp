/****************************************************************************//**
* @file Nate's functions
********************************************************************************/
#include"functions.h"


/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function finds the distance between two cities given the cities 
 * longitude and latiude. It does this by using the Haversine Formula.  
 *
 * @param[in] lon1 - longitude of the first city
 * @param[in] lon1 - longitude of the second city
 * @param[in] lat1 - latitude of the first city
 * @param[in] lat2 - latitude  of the second city
 *
 * @return distance - the distance between two points. 
 *
 ****************************************************************************/
double findDistance ( double lat1, double lat2, double lon1, double lon2 )
{
    double totalLon = lon2 - lon1;

    double totalLat = lat2 - lat1;

    double a, c, distance;

    a = pow(sin(totalLat/2), 2 ) + cos(lat1) * cos(lat2) * pow(sin(totalLon/2), 2 );

    c = 2 * atan2( sqrt(a), sqrt(1-a));

    distance = R * c;

    return distance;

}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function reads in the file that contains all the cities. It stores it
 * it in a map, along with the latitude and longitude coordinates  
 *
 * @param[in,out]    fin  - file input object
 * @param[in,out]    cities - map that contains all the cities and their lat and lon
 *
 ****************************************************************************/
void readInFile ( ifstream &fin, map<string, vector<double>> &cities )
{
    string lon, lat;
    double latNum, lonNum;
    string cityName;
    map<string, vector<double>>::iterator itr;

    //until end of file
    while (getline(fin, lat, '|'))
    {
          getline(fin, lon, '|');
 
	  //turn lat and lon into doubles from strings and from degrees into rads
	  latNum = stod(lat);

	  lonNum = stod(lon);

	  lonNum = (lonNum * 0.001 * M_PI) / 180;

	  latNum = ( latNum * 0.001 * M_PI) / 180;

          
	  getline(fin, cityName);

          //push into map
	  itr = cities.find(cityName);

	  if (itr == cities.end() )
          {
              cities[cityName].push_back(latNum);

	      cities[cityName].push_back(lonNum);
         
          }
   }

}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function reads in the file that contains the cities to visit. It reads it
 * into a map that will also tell us if we have visited that city when we do
 * out search 
 *
 * @param[in,out] fin - file input object
 * @param[in,out] visitCities - cities to visit
 * @param[in,out] cities - all cities
 *
 * @return numCities - number of cities
 *
 ****************************************************************************/
int readInCities (ifstream &fin, map<string, bool> &visitCities, map<string, vector<double>> &cities, map<string, vector<double>> &inputCities)
{
     string cityName;
     map<string, vector<double>>::iterator itr;
     int numCities;
     
     cout << "Cites to Visit: " << endl;

     //read in cities making sure that they exist in the file
     while ( getline(fin,cityName )) 
     {
         itr = cities.find(cityName);
	 
         if (itr == cities.end() )
	 {
              cout << "A city(s) to visit was not found in the original data set given! " 
		   << endl << "Exiting now..." << endl;

	      exit(1);
	 }
	
	//Insert our city to visit into inputCities
	 inputCities.insert(*itr);
	 visitCities[cityName] = false;

	 cout << endl << "\t" <<  cityName << endl;

	 ++numCities;
      }    

      //make sure there is enough cities in the file
      if (visitCities.size() < 3 )
      {
          cout << "Cites to vist file must have more than 2 cities in it! " 
	       << "Exiting now..." << endl;

	  exit(1);

      }

      return numCities;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function finds the shorstest curcuit, by finding all circuits and 
 * choosing the shortest one. It does this with a modified DFS. 
 *
 * @param[in,out]  visitCities - cities to visit
 * @param[in,out]  cities - all cities
 * @param[in]      city - city to check adjacent nodes of
 * @param[in]      distance - distace between nodes
 * @param[in,out]  circuits - stores all the circuits and their distances
 * @param[in]      path - keeps track of the path that we are on
 * @param[in]      numCities - number of cities to visit
 * @param[in]      startCity - original starting city.
 * @param[in,out]  min - holds the minimum distance value
 *
 ****************************************************************************/
void bruteForce (map<string, bool> visitCities, map<string, vector<double>> &cities, 
		 string city, double d, map<double, list<string>> &circuits, list<string> path,
		 int numCities, string startCity, double &min )
{
    map<double, list<string>>::iterator mapIt;
    map<string, bool>::iterator itr;
    double temp;
    int i = 0;

    //if we have this amount is means we have found a complete path
    if ( path.size()  == numCities - 1 )
    {
	//this is is to get the distance from end node back to start node
	temp = d + findDistance(cities[city][i], cities[startCity][i], cities[city][i+1], cities[startCity][i+1]);
	
        mapIt = circuits.find(temp);

	//cant find so add
	if (mapIt == circuits.end())
             circuits[temp] = path;
        {
		//see if its min
		if ( temp < min)
		  min = temp;
        }

	return;
    }
    
    //set the first one to true
    visitCities[city] = true;

    //do DFS on all adjacent nodes
    for ( itr = visitCities.begin(); itr != visitCities.end(); ++itr )
    {
         if (visitCities[itr->first] == false)
	 {
	     path.push_back(itr->first);

	     d += findDistance(cities[city][i], cities[itr->first][i], cities[city][i+1], cities[itr->first][i+1]);

             bruteForce(visitCities, cities, itr->first, d, circuits, path, numCities, startCity, min);  
	
	     //when we come back from the recursion... 
	     path.pop_back();

	     d -= findDistance(cities[city][i], cities[itr->first][i], cities[city][i+1], cities[itr->first][i+1]);
	 }
    }
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function just prints out the shortest path.
 *
 * @param[in,out] circuits - a map of tours and their distances
 * @param[in]     min - minimim distance
 * @param[in]     startCity - starting city
 *
 ****************************************************************************/
void printShortestPath ( map<double, list<string>> &circuits, double min, string startCity, double time )
{
     list<string>::iterator itr;
    
     cout << "\t" << startCity << " -> ";
     
     //print out tour 
     for (itr = circuits[min].begin(); itr != circuits[min].end(); ++itr)
         cout << *itr << " -> ";

     //print out first city with distance
     cout << startCity << endl;

     cout << "\t" << fixed << setprecision(3) << "Overall Distance of tour: " << min << "km" << endl;

     cout << "\tAlgorithm completed in " << time/CLOCKS_PER_SEC << " seconds" << endl;
     
}

