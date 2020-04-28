/****************************************//*
* Nathaniel Fagrey. HW2. CSC372
*******************************************/
#include "myGraph.h"

myGraph::myGraph( char fileName[], int start, int end, int k )
{
    strcpy( this->fileName, fileName );
    this->start = start - 1;
    this->end = end - 1;
    this->k = k;
}

void myGraph::operation( int testNum )
{
    queue<int> currentPath;
    fin.open( fileName );

    if( !fin.is_open() )
    {
        cout << "ERROR! Input file " << this->fileName << " failed to open!" 
             << endl;
        return;
    }

    createGraph( );

    findShortestPath( );

    printTest( testNum );
    printStorage();
    //printGraph();
    freeGraph( );

    fin.close();
    
    return;
}


void myGraph::createGraph()
{
    float weight;

    fin >> numVertices;

    graph = new ( nothrow ) float*[numVertices];
    storage = new ( nothrow ) float*[k];

    for( int i = 0; i < numVertices; ++i )
    {
        graph[i] = new ( nothrow ) float[numVertices];
    }

    for( int i = 0; i < k+1; ++i )
        storage[i] = new ( nothrow ) float[numVertices];

    for( int i = 0; i < numVertices; ++ i )
    {
        for( int j = 0; j < numVertices; ++j )
        {
            fin >> weight;

            if( weight > 0 && j > i )
                edges.push_back( { i, j } );

            if( weight <= 0 )
                weight = 99;

            graph[i][j] = weight;
        }
    }

    for( int i = 0; i < k + 1; ++i )
    {
       for( int j = 0; j < numVertices; ++j )
       {    
            storage[i][j] = 99;
       }
    }

}

// Psuedocode found on Chegg
void myGraph::findShortestPath( )
{ 
    list< pair<int, int> >::iterator itr;
    int s, t;

    #if (TESTING)
    for( itr = edges.begin(); itr != edges.end(); ++itr ) 
    {
        s = itr->first;
        t = itr->second;

        cout << s << " " << t  << endl;
    }
    #endif

    //for( int i = 0; i < numVertices; ++i )
    {
        storage[0][start] = 0;
    }

    for( int i = 1; i <= k; ++i )
    {
        for( itr = edges.begin(); itr != edges.end(); ++itr ) 
        {
            s = itr->first;
            t = itr->second;

            storage[i][t] = min( storage[i-1][t], storage[i-1][s] + graph[s][t] );
        }
    }
   
}

void myGraph::printTest( int testNum )
{
    int node = end;
    map<int,int>::iterator itr;
    int breaker = 0;

    cout << "===========================================" << endl;
    cout << "Test: " << testNum << endl;
    cout << "Start = " << start + 1 << " End = " << end + 1
         <<  " k = " << k << endl;
    
    cout << "Path: ";

    if( attributes[end].k < 0 )
        cout << "none" << endl;

    /*itr = path.find( end );

    if( itr == path.end() )
        cout << "none";
    
    else
    {
        node = myMin.first;

        cout << end + 1 << " ";

        while( node != -1 )
        {
            ++breaker;
            cout << node + 1 << " ";
            node = path[node];

            if( breaker >= 5 )
            {
                break;
            }
        }

    }
    */
    cout << endl;
}

void myGraph::freeGraph( )
{
    for( int i = 0; i < numVertices; ++i )
    {
       delete graph[i];
    }
    
    delete graph;
}

void myGraph::printStorage( )
{
    for( int i = 0; i < k+1; ++i )
    {
        for( int j = 0; j < numVertices; ++j )
        {
            cout << storage[i][j];

            if( storage[i][j] < 1 )
                cout << " ";

            else if( storage[i][j] < 10 )
                cout << "  ";
            
            else
                cout << " ";
        }

        cout << endl;
    }

    cout << endl;
    
}

void myGraph::printGraph()
{
for( int i = 0; i < numVertices; ++i )
    {
        for( int j = 0; j < numVertices; ++j )
        {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }

}