#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include<iostream>
#include<vector>
using namespace std;

class QuickSort
{
    public:
        void Sort( vector<int>&, int, int );

        int partition( vector<int>&, int, int );
};


#endif