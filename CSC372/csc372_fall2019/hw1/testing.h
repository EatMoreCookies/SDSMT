#ifndef TESTING_H
#define TESTING_H

#include<iostream>
#include<vector>
#include "quickSort.h"
#include "heapSort.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

void correctness();

void printVector( vector<int> arr );

void timeSorts( );

vector<int> fillVectorWithRandom( int size );

int getColumnWidth( int size );

bool makeSureItsSorted( vector<int> arr );
#endif
