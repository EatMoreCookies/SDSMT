/**************************************//*
* Nathaniel Fagrey. CSC372. Bonus Dynamic
*****************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
#include<stdio.h>
#include"Sum.h"
using namespace std;

int main( int argc, char* argv[] )
{
    ifstream fin;
    int N, size, num;
    vector<int> nums; 
    int TestNum = 0;

    if ( argc < 2 )
    {
        cout << "Not enough command line parameters given!" << endl;
        return 1;
    }

    char * fileName = argv[1];

    fin.open( fileName );

    if( !fin.is_open() )
    {
        cout << "File failed to open! " << endl;
        return 2;
    }

    do
    {
        ++TestNum;
        fin >> N >> size;

        nums.clear();
        for (int i = 0; i < size; ++i)
        {
            fin >> num;
            nums.push_back(num);
        }

        Sum k( nums, N, TestNum );
        k.operation( N );

    } while( !fin.eof() );

    return 0;
}