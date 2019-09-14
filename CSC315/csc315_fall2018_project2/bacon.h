/******************************************************************************
*@file
******************************************************************************/
#ifndef __BACON__H__
#define __BACON__H__

#include <cstring>
#include <string>
#include <list>
#include <unordered_map>
//#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iterator>
#include <queue> 
#include<limits.h>


using namespace std;

const int INFINIT = INT_MAX;

//function prototypes
void BFSSearch (unordered_map<string, list<string>> &movMap, unordered_map<string, list<string>> &actMap,
                unordered_map<string, int> &baconNum, unordered_map<string, list<string>> &baconPath, string root );
void makeBaconMap ( unordered_map<string, list<string>> &actMap, unordered_map<string, int> &baconNum, unordered_map<string, list<string>>
               &baconPath);
bool actorInsert(string &actor, string &movie);
bool movieInsert(string &key,  list<string> &adjlist);
bool parser(string & inputstr, unordered_map<string, list<string> > &movieMap, unordered_map<string, list<string> > & actorMap);
string menu();
void printBN (unordered_map<string, int > &baconNum, int bn );

void longestPaths (unordered_map<string, int> &baconNum, int histogram[] );     
bool checkValidActor ( unordered_map<string, list<string>> &actorMap, string rootActor );
int histoGram(unordered_map<string, int> &baconNum, int histogram[]);
void printHistogram ( int histogram[], int INF );
void findShortestPath ( unordered_map<string, list<string>> &baconPath, string actor, string rootActor,
               unordered_map<string, int> &baconNum );

void outFile(unordered_map<string, int> &baconNum, int bn, string file);

#endif


