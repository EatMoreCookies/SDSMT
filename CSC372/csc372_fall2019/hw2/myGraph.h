/****************************************//*
* Nathaniel Fagrey
*******************************************/

#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#define TESTING 1

#include<iostream>
#include<cstring>
#include<fstream>
#include<queue>
#include<map>
#include<stack>
#include<cstdlib>
#include<cmath>
#include<list>
using namespace std;

const int aLargeNumber = 999999;

class myGraph
{
    public:
        myGraph( char fileName[], int start, int end, int k );
        void operation(int testNum );
    
    private:

        // Private Methods
        void createGraph();
        void freeGraph();
        void printTest( int testNum );
        void findShortestPath( );
        void printStorage( );
        void printGraph( );

        // Private Members
        ifstream fin;
        int start, end, k;
        char fileName[20];
        float ** graph;
        int numVertices = 0;;

        struct data
        {
            int parent;
            int k;
        };

        data attributes[20];

        float ** storage;
        bool visited[10] = {0};
    
        map<int, int> cost;
        list< pair<int, int> > edges;
};



#endif // !MY_GRAPH_H
