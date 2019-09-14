#include "functions.h"

/**************************************************************************//**
* @author Haley Linnig
*
* @par Description:
* This function will find the shortest path from the given starting city
* back to the given starting city while hitting every city given. It will do
* this using Prim's algorithm to create a minimum spanning tree by placing
* each city's distance into a priority queue and finding the smallest distance.
* It will then do a preorder traversal through the mimimum spanning tree to
* give the shortest path.
*
* @param[in] numCities - Number of cities to visit
* @param[in] inputCities - Holds names of all cities to visit, their lat & lon
* @param[in] startCity - Name of city to start with
*
* @return 0 - program returned correctly
*
******************************************************************************/

int primAlg(int numCities, map<string, vector<double>> inputCities, string startCity)
{
    vector<city> cityList;
    vector<int> mst;
    int i, j, count;
    priority_queue<city> vertexQ;
    city temp;
    double totalDist = 0;
    bool contTrav = true;

    //List of cities must be large enough to hold data for ALL cities
    cityList.resize(numCities);
    //Fill cityList with city indexes, cityList[0] will contain the starting city
    createVector(inputCities, startCity, cityList);

    //Initialize all distances to -1
    for(i = 0; i < numCities; i++)
    {
        //Resize vector of distances to fit all cities
        cityList[i].cityDistance.resize(numCities);

        for(j = 0; j < numCities; j++)
            cityList[i].cityDistance[j] = -1;
    }

    //Create an adjacency matrix to hold distances from one city to another
    createAdjMatrix(inputCities, cityList);
    //Set first city's visited status to true
    cityList[0].visited = true;

    //Put first city into priority queue
    vertexQ.push(cityList[0]);

    //While we have something in the queue, we need to deal with it
    while(!vertexQ.empty())
    {
        //Set temp = whatever is on top and pop it off
        temp = vertexQ.top();
        vertexQ.pop();

        //Current city index = temp.index;
        //Set that city's visited status to true
        cityList[temp.index].visited = true;

        //i represents the second city that we are reaching with our current city (temp)
        for(i = 0; i < numCities; i++)
        {
            //If we haven't visited this city yet, we need to set its previous node and distance
            if(cityList[i].visited == false &&  cityList[i].distance > cityList[temp.index].cityDistance[i])
            {
                cityList[i].prevCity = temp.index;
                cityList[i].distance = cityList[temp.index].cityDistance[i];
                vertexQ.push(cityList[i]);
            }
        }

    }

    //Set children for each city
    for( i = 1; i < numCities; i++)
    {
        temp = cityList[i];
        cityList[cityList[i].prevCity].children.push_back(temp);

        //If more than one item in vector of city children, then sort them by distance
        if(cityList[cityList[i].prevCity].children.size() > 1)
            sort(cityList[cityList[i].prevCity].children.begin(), cityList[cityList[i].prevCity].children.end(), sortFunc);
    }

    //Print out mst path
    j = 0;
    cout << "\t" << cityList[j].cityName << " ";

    //Print out all nodes and children
    for(i = 0; i < cityList.size() - 1; i++)
    {
        //Set continue traversal value to true
        contTrav = true;

        //If node has 0 children
        if(cityList[j].children.size() == 0)
        {
            //While we aren't at a branching node
            while(cityList[j].children.size() <= 1 || contTrav == true)
            {
                //Set current node back to previous node
                j = cityList[j].prevCity;

                //Once we have reached a branching node
                //Check if we have visited all of its children already
                if(cityList[j].childCount == cityList[j].children.size() - 1 || cityList[j].children.size() <= 1)
                    contTrav = true;
                else
                    contTrav = false;
            }

            //We have found a branching node that doesn't have all of its children explored
            //Increment index of child count
            //Set next city to be node's next child path
            cityList[j].childCount++;
            count = cityList[j].childCount;

            cout << "-> " << cityList[cityList[j].children[count].index].cityName << " ";
            totalDist += cityList[cityList[j].children[count].index].distance;
            j = cityList[j].children[count].index;
        }

        //If node has 1 child
        else
        {
            cout << "-> " << cityList[cityList[j].children[0].index].cityName << " ";
            totalDist += cityList[cityList[j].children[0].index].distance;
            j = cityList[cityList[j].children[0].index].index;

        }

    }
    totalDist += cityList[j].cityDistance[0];
    cout << "-> " << cityList[0].cityName << endl;
    cout << "\tOverall distance of tour: " << totalDist << " km " << endl;

    return 0;

}

/**************************************************************************//**
* @author Haley Linnig
*
* @par Description:
* This function will create an adjacency matrix to hold the distance from one
* city to another. This information will be stored within the vector<double>
* cityDistance with the index representing the city that we are "traveling" to.
* It will set the a city's distance to itself as 0. It will calculate a city's
* distance to a secondary city and also update that distance for the secondary
* city to the particuar city. It will calculate the distance by using the
* Haversine Formula. So, we will subtract the second city's latitude from the
* first city's latitude(dlat) and do the same for longitude. Then, it'll take
* the sin of the dlat divided by two times the cosine of city one's latitude
* times the cosine of city two's latitude and times the sin of dlon divided by
* two to the power of two. This value (a) will be used in another equation where
* we will multiply 2 and the arc tangent of the square root of a and the square
* root of 1 - a. The distance will finally be calculated by multiplying that
* value by 6373 (the radius of the Earth)
*
* @param[in] inputCities - Holds names of all cities to visit, their lat & lon
* @param[in] cityList - Vector of class city that holds all city data
*
* @return none
*
******************************************************************************/

void createAdjMatrix(map <string, vector<double>> inputCities, vector<city> &cityList)
{
    map<string, vector<double>>::iterator it;
    int i, j, numCities = cityList.size();
    double dlat, dlon, lat1, lon1, lat2, lon2, a, d;

    //Go through every city's path to each other
    for(i = 0; i < numCities; i++)
    {
        for( j = 0; j < numCities; j++)
        {
            //Distance from a city to itself is 0
            if(i == j)
                cityList[i].cityDistance[j] = 0;

            //If distance hasn't been filled, fill it
            if(cityList[i].cityDistance[j] == -1)
            {
                //Find City i
                it = inputCities.find(cityList[i].cityName);
                lat1 = it->second[0];
                lon1 = it->second[1];

                //Find City j
                it = inputCities.find(cityList[j].cityName);
                lat2 = it->second[0];
                lon2 = it->second[1];

                //Calculate distance from i to j
                cityList[i].cityDistance[j] = findDistance(lat1, lat2, lon1, lon2);
                cityList[j].cityDistance[i] = cityList[i].cityDistance[j];
            }
        }
    }

    return;
}

/**************************************************************************//**
* @author Haley Linnig
*
* @par Description:
* This function will store city name and index for every single city's info
* by iterating through the map. Storing the city name allows for accessing the
* map easily but also allowing for using a numerical index. It will also swap
* whatever our starting city is to the front of our list.
*
* @param[in] inputCities - Holds names of all cities to visit, their lat & lon
* @param[in] startCity - Name of city to start with
* @param[in] cityList - Vector of class city that holds all city data
*
* @return none
*
******************************************************************************/
void createVector(map<string, vector<double>> inputCities, string startCity, vector<city> &cityList)
{
    map<string, vector <double>>::iterator it;
    int i = 0;
    string tempCity;

    //For every city, store city name and index
    for(it = inputCities.begin(); it != inputCities.end(); ++it)
    {
        //Put names into cityList for easy access
        cityList[i].cityName = (it->first);
        cityList[i].index = i;
        cityList[i].children.resize(0);

        //startCity should be at the front of our list of cities
        if(it != inputCities.begin() && it->first == startCity)
        {
            //Swap startCity to front
            tempCity = cityList[0].cityName;
            cityList[0].cityName = cityList[i].cityName;
            cityList[i].cityName = tempCity;
        }

        i++;
    }

    return;
}

/**************************************************************************//**
* @author Haley Linnig
*
* @par Description:
* This function will allow the standard library sort to sort cities by their
* distances.
*
* @param[in] cityOne - Holds value of one city
* @param[in] cityTwo - Holds value of one city
*
* @return true
* @return false
*
******************************************************************************/

bool sortFunc(city cityOne, city cityTwo )
{
    if(cityOne.distance < cityTwo.distance)
        return true;

    return false;
}
