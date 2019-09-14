/**************************************************************************//**
*@file
******************************************************************************/

#include "bacon.h"

/*************************************************************************//**
 * @author Nathaniel Fagrey. 
 *
 * @par Description: 
 * This function creates a two maps: One to hold the bacon number and one
 * to hold the parent root and actor. 
 *
 * @param[in,out]   actMap  - map of the actors/actresses
 * @param[in,out]   baconNum - a map to hold the bacon number and the actor
 * @param[in,out]   baconPath - a map to hold the parent movie and actor of 
 *                              each node
 *
 ****************************************************************************/
void makeBaconMap ( unordered_map<string, list<string>> &actMap, unordered_map<string, int> &baconNum, unordered_map<string, list<string>> 
	       &baconPath)
{
        list<string> tempList;

        tempList.clear();

        unordered_map<string, list<string>>::iterator itr;

        //getting size
        int size = actMap.size();
      
        //set at begining of map
        itr = actMap.begin();
       

        while (size > 0 )
        {    
	     //insert
             baconNum[itr->first] = INFINIT;

	     baconPath[itr->first] = tempList;

             --size;

             ++itr;
        }  
        	

        return;
}


/*************************************************************************//**
 * @author Nathaniel Fagrey. 
 *
 * @par Description: 
 * This function searches through the map, finding shortest paths and the 
 * bacon numbers of the actor nodes. 
 *
 * @param[in,out]   movMap - map of the movie nodes
 * @param[in,out]   actMap  - map of the actors/actresses
 * @param[in,out]   baconNum - a map to hold the bacon number of all the actors
 * @param[in,out]   baconPath - a map to contain the parent movie and actor node
 *                              of a particular actor. 
 * @param[in]       root - root actor 
 ****************************************************************************/
void BFSSearch (unordered_map<string, list<string>> &movMap, unordered_map<string, list<string>> &actMap,
                unordered_map<string, int> &baconNum, unordered_map<string, list<string>> &baconPath, string root )
{

    queue<string> Q;
        
    string actor;

    list<string>::iterator it1, it2;

    list<string> path;

    baconNum[root] = 0;;

  
    //push the root first
    Q.push(root);

    while (!Q.empty())
    {
           
	 actor = Q.front();

	 Q.pop();

         //go through all the nodes in the actors adjacency lists
	 for (it1 = actMap[actor].begin(); it1 != actMap[actor].end(); ++it1)
	 {
	      //go through all the nodes in the movies adjacency list
	      for (it2 = movMap[*it1].begin(); it2 != movMap[*it1].end(); ++it2 )
              {
		      
		   //if the bacon number = INFINITY
		   if (baconNum[*it2] == INFINIT)
		   {
	               path.push_back(*it1);

		       path.push_back(actor);

		       baconPath[*it2] = path;	       

		       baconNum.erase(*it2);
		       
		       baconNum[*it2] = baconNum[actor] + 1;

                       Q.push(*it2);

		       path.clear();
                   }

	      }
              //erase for better memory
	      movMap.erase(*it1);

	 }
         
	 actMap.erase(actor);

    }
}

/*************************************************************************//**
 * @author Nathaniel Fagrey. 
 *
 * @par Description: 
 * This function makes sure that the root actor entered on the command line
 * is actually in the data file. 
 *
 * @param[in,out]   actorMap  - map of the actors/actresses
 * @param[in]       rootActor - the root actor entered on the command line
 *
 * return false - actor not found
 * return true  - actor found
 *
 ****************************************************************************/
bool checkValidActor ( unordered_map<string, list<string>> &actorMap, string rootActor )
{
    
    unordered_map<string, list<string>>::iterator itr;

    itr = actorMap.find(rootActor);
    
    //if root actor not found
    if ( itr == actorMap.end() )
    {
        cout << "Sorry, " << rootActor << " was not found in the data file. " << endl;

        cout << "Exiting now..." << endl;

        return false;

    }

    return true;
}
/*************************************************************************//**
 * @author Nathaniel Fagrey. 
 *
 * @par Description: 
 * This function finds the actors with the largest bacon numbers and prints
 * them to the screen. 
 *
 * @param[in,out]   baconNum - map that contains bacon number of actor or 
 *                             actress.
 * @param[in,out]   histogram - an array that holds the frequency that a 
 *                              bacon number appears
 *
 *
 ****************************************************************************/
void longestPaths ( unordered_map<string, int> &baconNum, int histogram[] )
{
    unordered_map<string, int>::iterator itr;

     int i;

     list<string> longest;
     
     //find the index where the largest bacon number occurs
     for ( i = 0; histogram[i] != 0; ++i )
     {}

     //subtract one
     i--;

     cout << endl;

     //print out the names as we go through the map
     for ( itr = baconNum.begin(); itr != baconNum.end(); ++itr )
     {   
	  //if it equals the bacon number print it
          if ( itr->second == i )
                  cout << itr->first << endl;

     }

}
/*************************************************************************//**
 * @author Nathaniel Fagrey. 
 *
 * @par Description: 
 * This function prints out the shortest path from the root actor to another
 * one. This function also makes sure the actor entered exists or is actually
 * connected to the root.  
 *
 * @param[in,out]   baconPath - map that the parent movie and parent actor nodes
 *                              for a actor node
 * @param[in]       actor - the actor to find the path to
 * @param[in]       rootActor - the root actor for the problem
 * @param[in,out]   baconNum - a map that contains the bacon number of a actor
 *
 ****************************************************************************/
void findShortestPath ( unordered_map<string, list<string>> &baconPath, string actor, string rootActor,
	       unordered_map<string, int> &baconNum )
{
     cout << endl << "Searching for Actor: " << actor << endl;
     unordered_map<string, list<string>>::iterator itr;    

     string parentActor, parentMovie;

     list<string> path;
     
     list<string>::iterator it;
     
     itr = baconPath.find(actor);

     
     //make sure that the person is in the data file
     if (itr == baconPath.end())
     {
         cout << endl << "The actor you have entered was not found in the data file provided." 
	      << endl << "Either try another actor or update the data file. " << endl
	      << endl;

	 return;

     }

     //see if there is even a path from root
     if ( baconNum[actor] == INFINIT )
     {
         cout << endl << "No path from " << actor << " to " << rootActor << " could be found. " 
	      << endl << endl;

	 return;
     }

     //in case the root actor is entered
     parentActor = actor;

     cout << endl << actor << endl;

     //until we hit the root node
     while ( parentActor != rootActor )
     {
         //pop from path and print
	 path = baconPath[parentActor];
	     
	 parentMovie = path.front();
        
	 cout << endl << "Who starred in the Movie - " << parentMovie << endl;

      	 path.pop_front();

	 parentActor = path.front();

	 cout << endl << "Along with actor - " << parentActor << endl;
	 
	 path.pop_front();
     }
	
}

/*************************************************************************//**
 * @author Nathaniel Fagrey.
 *
 * @par Description:
 * This function prints out the histogram along with the average path length
 *
 * @param[in,out]   histogram - an array that holds the frequency that a
 *                              bacon number appears
 * @param[in]       INF - the number of actors that are not connected
 *
 ****************************************************************************/
void printHistogram ( int histogram[], int INF )
{
    int index = 0;
    double avgPath = 0;
    int validActors = 0;

    cout << endl << endl << "Histogram of Bacon numbers" << endl << endl;

    cout << "#        Freq" << endl
       << "-----------------" << endl << endl;

    //when we hit zero we have hit the nodes that have INFINITY as a bacon number
    while ( histogram[index] != 0 )
    {
        cout << index << "       " << histogram[index] << endl;

        avgPath += index * histogram[index];

	validActors += histogram[index];
	
	++index;
    
    }

    //print the nodes without a path and the average path length
    cout << "Inf     " << INF << endl << endl;

    avgPath /= double(validActors);

    cout << fixed << setprecision(6) << "The average path length is: " << avgPath << endl;
}


