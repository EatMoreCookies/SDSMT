/*************************************************************************//**
 * @file 
 *
 * @mainpage Traveling Saleman Problem
 * 
 * @section course_section Course Information 
 *
 * @author Nathaniel Fagrey, Haley Linnig
 * 
 * @date December 5, 2018
 * 
 * @par Professor: 
 *         Dr. Larry Pyeatt
 * 
 * @par Course: 
 *         CSC 315- M002 - 2:00pm
 * 
 * @par Location: 
 *         McLaury - 310
 *
 * @section program_section Program Information 
 * 
 * @details This program finds two solutions to the Traveling Salesperson's Problem.
 * The TSP tries to solve the problem in which a traveling salesperson has to visit a list
 * of cities and return to the one they started in as efficiently as possible  (a.k.a 
 * travel the least amount of distance to do a circuit). This kind of path is called a 
 * Hamaliton Circuit. 
 *
 * In the first solution we will try a brute force approach in which the all the possible
 * circuits are found with their distances. The shortest circuit is then picked. In the second 
 * approach, a minimum spanning tree will be constructed to find a close but not exact 
 * solution to the problem. The MST algorithm will be much faster though. 
 *
 * A menu is presented in which the user can select a histogram or to find the shortest 
 * circuit if they provide a starting city. Both algorithms will be used to find the 
 * shortest path, and their results and paths printed on the screen.  
 *
 * @section compile_section Compiling and Usage          
 *
 * @par Compiling Instructions: 
 *      No special compiling instructions
 * 
 * @par Usage: In order to use this program you must specify on the command 
               line the program, list of cities to visit, and a file of 
	       visited cities.
      
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  ------------------------------------------------------------- 
   <a href="git@gitlab.mcs.sdsmt.edu:7416949/csc315_fall2018_project3.git">
   @endverbatim
 *
 ****************************************************************************/
#include"functions.h"



/*************************************************************************//**
 * @author Haley Linnig, Nathaniel Fagrey
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
int main( int argc, char **argv )
{
    string startCity;
    double distance = 0;
    int numCities;

    ifstream fin;
    ifstream fin1;
    clock_t t;
    
    map<string, vector<double>> cities;
    map<string, vector<double>> inputCities;
    map<string, bool>  cities2Visit; 
    map<double, list<string>> circuit;

    double min = INT_MAX;
    
    list<string> path;

    map<string, bool>::iterator test;  

    //check command line arguments.	
    if ( argc != 3 )
    {
        cout << "TSP requires 3 command line arguments:  % TSP datafile1.txt datafile2.txt"
	     << endl << "Exiting now..." << endl;
             
        exit(1);	
    }
    
    //open file    
    fin.open(argv[1]);

    fin1.open(argv[2]);

    
    //check for success
    if (!fin || !fin1 )
    {
       cout << "Input file(s) failed to open! " << endl << "Exiting now..." << endl;
       return -1;
    }

    //read in first file
    readInFile (fin, cities);

    numCities = readInCities(fin1, cities2Visit, cities, inputCities);

    cout << endl << "Please enter the city you would like to start with: ";

    getline(cin, startCity);

    //make sure start city is in visitCities file
    test = cities2Visit.find(startCity);

    if (test == cities2Visit.end())
    {
        cout << "Entered city does not exist in the cities to visit file provied!" 
	    << endl << "Exiting now..."<< endl;
	 
	return -1;
    }

    
    //brute force algorithm
    cout << endl << endl << "Tour Computed by brute force algorithm: " << endl;

    t = clock();

    bruteForce (cities2Visit, cities, startCity, distance, circuit, path,
		    numCities, startCity, min );
   
    t = clock() - t;

    printShortestPath (circuit, min, startCity, t);

    cout << endl << endl << "Tour computed by MST algorithm: " << endl;
    
    t = clock();

    primAlg(numCities, inputCities, startCity);	

    t = clock() - t;

    cout << "\tAlgorithm completed in " << double(t)/CLOCKS_PER_SEC << " seconds " << endl;    
 

    return 0;

}
