 /***************************************************************************//**
 * @file
 *
 * @mainpage Program 2 - Six Degrees of Kevin Bacon
 *
 *
 * @section course_section Course Information
 *
 * @authors Robert Minick
 *          Nathaniel Fagrey
 *
 * @date November 14, 2018
 *
 * @par Professor:
 *      Dr. Larry Pyeatt
 *
 * @par Course:
 *         CSC315 - Section 2 - 2:00pm
 *
 * @par Location:
 *        McLaury Bldg: Room 310
 *
 * @section program_section Program Information
 *
 * @details
 * The program takes one required argument, the name of a movie database file.
 * Each line of this input text file describes a movie, and consists of fields
 * separated by the forward slash character (/). The first field is the movie
 * name. Remaining fields are the names of the actors/actresses who appeared in
 * the movie.
 * An adjacency list will be used to represent a weighted graph.
 * The graph is used to generate shortest paths from Kevin Bacon to every other
 * actor/actress. Unweighted edges will allow a simple breadth-first search (BFS) 
 * to find shortest paths. From this a minimum spanning tree (MST) will be
 * created from the graph. The MST can be traversed from the start (Kevin Bacon) or
 * any other actor/actress, to any other actor/actess, by generating their Bacon
 * numbers by counting the number of links between them.
 * In addition to computing individual Bacon numbers, the program will perform
 * statistical analysis on the graph. After reading in the movie database and
 * assigning Bacon numbers, print a histogram of Bacon numbers, the average path
 * length (for actors who have been assigned Bacon numbers), and the longest
 * shortest paths (actors with the highest Bacon numbers).
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  -------------------------------------------------------------
   <a href="git@gitlab.mcs.sdsmt.edu:7416949/csc315_fall2018_project2.git">
   
   GitLab Commits.

   @endverbatim
*
*****************************************************************************/

#include <iostream>
#include "bacon.h"

using namespace std;

/*************************************************************************//**
* @author Robert Minick
*
* @par description
* This function is the main function from which the program will execute and
* exit. Input requires 2 parameters, in execution command and an input file
* name.
*
* @param [in]	argc	integer value holding size of argv array
* @param [in]	argv	variable name of commandline array
* @return	0	program ran successfully
* @return	-1	program exited with an error
*
*****************************************************************************/

int main(int argc, char* argv[])
{
   // variable declarations
   ifstream fin;
   string infile;
   string rootActor;
   string option, fileName;
   unordered_map<string, list<string>> movieMap;
   unordered_map<string, list<string>> actorMap;
   unordered_map<string, int> baconNum;
   unordered_map<string, list<string>> baconPath; 
    
   int Inf, bn;
   
   // check for commandline arguement
   if(argc > 3 || argc < 2)
   {
      cout << "This program requires 2 or 3 parameters, an execution command, ";
      cout << "an input data file name. and an optional name string" << endl;
      cout << "If no name string is included, the name string will default to ";
      cout << " 'Kevin Bacon', Program exiting" << endl;
      return -1;
   }
   infile = argv[1];
   // open file
   fin.open(infile);
   if(!fin)
   {
      cout << "Input file did not open, Program exiting" << endl;
      return -1;
   }

   // set actor string
   if(argc == 2)
   {
      rootActor = "Bacon, Kevin";
   }
   else
      rootActor = argv[2];
   
   while(fin)
   {
      getline(fin, infile);
      parser(infile, movieMap, actorMap);
   };   
  
  
   //check to make sure the root actor is in the data file. 
   if (!checkValidActor(actorMap, rootActor ))
   	  return -1; 


   cout << endl << "Root Actor - " <<  rootActor << endl;
   
   //make the baconMap
   makeBaconMap (actorMap, baconNum, baconPath );   
  
   //BSF search. This will cause the 
   BFSSearch (movieMap, actorMap, baconNum, baconPath, rootActor );
   
   do
   {
      //so it gets reset every time;
      //
      int histogram[1000] = {0}; 
        
      //get menu option
      option = menu();

      if ( option == "histogram")//function to make and print histogram
      {
         Inf = histoGram (baconNum, histogram );
         printHistogram (histogram, Inf );
      }
      else if ( option == "longest" ) //function to print out longest paths
      {
           histoGram(baconNum, histogram);

	   longestPaths( baconNum, histogram );
      }

      else if (option == "baconNum" )
      {
           cout << "Please enter the bacon number that you would like to search for: ";
           cin.clear();
	   cin >> bn;
            
	   cout << endl;

	   if ( bn > 6 || bn < 1 )
           {
              printBN (baconNum, bn );
              cin.ignore();
           }

	   else
	   {  
               cout << "Data too large...Printing to file instead. " << endl;
	       
	       cout << "Please enter the out file you want to go to: ";

	       cin.ignore();

	       getline(cin, fileName );

	       outFile(baconNum, bn, fileName );
               cin.clear(); 
           } 

      }

      else if ( option == "quit" )
	      return 0;

      else
	 findShortestPath( baconPath, option, rootActor, baconNum  );
	 //function to print out the shortest path using option as the name to search for
    
   }while( option != "quit");   
   
   fin.close();
   
   
   return 0;
}

