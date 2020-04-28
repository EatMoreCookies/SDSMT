#ifndef Sum_H
#define Sum_H
#include<vector>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std; 


class Sum
{
    public:
        Sum( vector<int> nums, int N, int TestNum );
        void operation( int N );

    private:
        int N;
        vector<int> nums;
        vector<int> bestNums = {99999};
        int runningSum = 0;
        int ** storage;
        map<int, int> rows;
        vector<int> solutions;
        int TestNum;
        
        void createStorage();
        void printSolution();
        void findSolution();
        pair<int, int> min;

};


#endif
