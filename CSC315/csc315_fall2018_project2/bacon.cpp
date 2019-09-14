/****************************************************************************//**
* @file 
********************************************************************************/

#include "bacon.h"

/*************************************************************************//**
 * @author Robert Minick
 *
 * @par Description: 
 * This function will take a string seperated by
 * a "/" and parse the list into two seperate stl list strings containing
 *
 * @param[in]       inputstr  -  string variable holding movie and actor information
 * @param[in,out]   movieMap  -  map of all Movies and their adjacency lists	
 * @param[in,out]   actorMap  -  map of all the actors and their adjacency lists
 * 
 * @return      false   if the string is empty
 * @return      true    everything in the map and string is fine
 *
 ****************************************************************************/
bool parser(string & inputstr, unordered_map<string, list<string> > &movieMap, unordered_map<string, list<string> > & actorMap)
{
    // Variable declaration and object initializers
    stringstream ss;
    string movieTitle;
    string actorName;
 
    list<string> tempActors; 
    list<string> tempMovies;
    list<string> actorList;
    unordered_map<string,list<string> > :: iterator itr;
    unordered_map<string,list<string> > :: iterator listItr;    

    // turn input stream into string     
    ss << inputstr;
   
    // read in string and error check for empty string
    getline(ss, movieTitle, '/');
    if(movieTitle.empty()) return false;

    //fill movieNode struct
     
    //tempMovieNode.movie = movieTitle; 
    //cout << "Movie Title: " << movieTitle << endl;
    tempMovies.push_back(movieTitle);

    while(getline(ss,actorName,'/'))
    {
  
       // actorMap.insert(make_pair(actorName, tempMovies));
            
  
        if(actorName.empty()) 
           return false;
        else
        {
                   
           itr = actorMap.find(actorName);
           if(itr == actorMap.end())
              actorMap[actorName] = tempMovies;
           else
           {
             itr->second.push_back(movieTitle);   
           }   
           
           tempActors.push_back(actorName);
                 
        } 
                
    };
    
      
    //movieMap.insert(make_pair(movieTitle,tempActors));

    movieMap[movieTitle] = tempActors;
    
    return true;
}


