/****************************************//*
* Nathaniel Fagrey
* CSC 372. HW2
*******************************************/

#include<iostream>
#include "myGraph.h"
#include<stdlib.h>
using namespace std;

int main(int argc, char * argv[])
{
    int i = 1;
    char * fileName = nullptr;
    int start, end, k;
    int testNum = 0;

    do
    {
        testNum += 1;
        fileName = argv[i];
        i++;
        start = atoi( argv[i] );
        i++;
        end = atoi( argv[i] );
        i++;
        k = atoi( argv[i] );
        i++;

        myGraph graph( fileName, start, end, k );
        graph.operation( testNum );
        
    } while( i < argc );


    return 0;
}
