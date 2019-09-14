#ifndef __EASYEIGHT_H
#define __EASYEIGHT_H

#include "Actor.h"
#include <cmath>
#include <queue>
#include<map>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<iostream>
#include<ctime>
using namespace std;

const int TOOMANY = 3;

enum spendAPVals{MOVE = 1, ATTACK = 2, ENDTURN = 3};

/* Point distance struct */
struct pointDistance
{
    int x;
    int y;
    vector<direction> path = {};
};

class EasyEight : public Actor
{


    public:

    direction evadeDir = STAY;

    /* Methods */
        int calcDist( int x1, int y1, int x2, int y2 );

        direction move( MapData map, PositionData status );

        direction moveToUnvisited(MapData map,PositionData status);

        void initToVisitList(MapData map, PositionData status);

        direction attack( MapData map, PositionData status );

        attributes setAttribute( int pointsAvailable, attributes baseStats );

        int spendAP( MapData map, PositionData status );
        
        void updateMap( MapData map, PositionData status);
        
        void printMyMap( MapData map );
        
        bool clearShot ( int, int, int, int );

        direction getAttackDir ( int, int, int, int );

        direction contingencyPlan ( pair<int,int>, map<pair<int,int>, int >, MapData, PositionData);
   
        vector<direction> findShortestPath (pair<int, int>, MapData, PositionData );
        
        direction determineNextMove ( int, int );

        direction backOut ( direction );

        void operator= ( attributes );      

        void setMyMap( MapData, PositionData );


        direction evade(PositionData, pair<int, int>, MapData);
    
    /* Constructors/Destructors */
        EasyEight();
        ~EasyEight();

    /* Our Variables */
    private:
        direction moveDir = STAY; 
        
        
        vector<pointDistance> toVisit;
        vector<int> myMap;
        attributes myStats; 
};



#endif
