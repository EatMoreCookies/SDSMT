#include"../src/EasyEight.h"
#include"../src/MapData.h"
#include"../src/PositionData.h"
#include "catch.hpp"

const int ID = 1;

TEST_CASE ("Can we find the right place to move if its right above us")
{
    EasyEight ourTank;
    PositionData status;
    
    //make a 3x3 map
    MapData Map(3, 3);

    pair<int,int> endCoords (1, 1);


    Map.map[7] = ID;
    status.id = ID; 
    status.game_x = 1;
    status.game_y = 1;

    ourTank.setMyMap( Map, status );

    vector<direction> expected = {UP};

    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE (expected == actual);
}

TEST_CASE ("Can we find the shortest path given end coordinates in a clear field")
{
    EasyEight ourTank;
    PositionData status;

    //make a 3x3 map
    MapData Map(3, 3);

    pair<int,int> endCoords (0, 0);


    Map.map[7] = ID;
    status.id = ID;
    status.game_x = 1;
    status.game_y = 1;

    ourTank.setMyMap( Map, status );

    vector<direction> expected = {UPLEFT, UP};
    
    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE (expected == actual);
}

TEST_CASE ("Find a place to move to in a larger map")
{
    EasyEight ourTank;
    PositionData status;
    MapData Map(5, 5);
    
    pair<int, int> endCoords(2, 1);

    Map.map[5] = ID;
    status.id = ID;
    status.game_x = 2;
    status.game_y = 1;

    ourTank.setMyMap ( Map, status );


    vector<direction> expected = {UPRIGHT, DOWNRIGHT};

    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE(expected == actual);
}


TEST_CASE ("Return empty vector if given negative coords")
{
    EasyEight ourTank;
    PositionData status;
    MapData Map(5, 5);
    
    pair<int, int> endCoords(-2, -1);

    Map.map[5] = ID;
    status.id = ID;
    status.game_x = 2;
    status.game_y = 1;

    ourTank.setMyMap ( Map, status );


    vector<direction> expected = {};

    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE(expected == actual);
}


TEST_CASE ("Find a place to move to in a larger map starting on edge")
{
    EasyEight ourTank;
    PositionData status;
    MapData Map(5, 5);

    pair<int, int> endCoords(4, 0);

    Map.map[5] = ID;
    status.id = ID;
    status.game_x = 2;
    status.game_x = 1;

    ourTank.setMyMap( Map, status );


    vector<direction> expected = {UPRIGHT,RIGHT, RIGHT, RIGHT};

    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE(expected == actual);
}


TEST_CASE ("Find a place to move with obstacles")
{
    EasyEight ourTank;
    PositionData status;
    MapData Map(5, 5);


    pair<int, int> endCoords(4, 0);

    Map.map[19] = ID;
    status.id = ID;
    status.game_x = 4;
    status.game_y = 3;
    
    attributes baseStats;

    baseStats.tankRadar = 10;
    baseStats.tankRadar = 10;    

    Map.obstacleMap[14] = 'R';
    Map.obstacleMap[13] = 'W';
    Map.obstacleMap[24] = 'R';

    ourTank.setAttribute(10, baseStats );

    ourTank.setMyMap( Map, status );

    vector<direction> expected = {LEFT, UPLEFT, UPRIGHT, UPRIGHT};
    
    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE(expected == actual);
}


TEST_CASE ("Return an empty vector if blocked in")
{
    EasyEight ourTank;
    PositionData status;
    MapData Map(5, 5);

    pair<int, int> endCoords(4, 4);

    attributes baseStats;

    baseStats.tankRadar = 10;
    baseStats.tankRadar = 10;

    Map.map[0] = ID;
    status.id = ID;
    status.game_x = 0;
    status.game_y = 0; 


    Map.obstacleMap[1] = 'R';
    Map.obstacleMap[5] = 'W';
    Map.obstacleMap[6] = 'R';

    ourTank.setAttribute( 10, baseStats );

    ourTank.setMyMap( Map, status );

    
    vector<direction> expected = {};
    
    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE(expected == actual);
}

TEST_CASE ("Do we wrap around the 1D array")
{
    EasyEight ourTank;
    PositionData status;
    MapData Map(3, 3);

    attributes baseStats;

    pair<int,int> endCoords(0, 0);

    Map.map[5] = ID;
    status.id = ID;
    status.game_x = 2;
    status.game_y = 1;

    ourTank.setAttribute( 10, baseStats );

    ourTank.setMyMap( Map, status );

    vector<direction> expected = {UPLEFT, LEFT};

    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE ( expected == actual );
}

TEST_CASE ( "Given a large unknown map, can we find the right direction to it")
{

    EasyEight ourTank;
    PositionData status;
    MapData Map(20, 20);

    pair<int,int> endCoords(0, 0);

    Map.map[399] = ID;
    status.id = ID;
    status.game_x = 19;
    status.game_y = 19;

    ourTank.setMyMap ( Map, status );

    vector<direction> expected;


    expected.resize(19); 

    std::fill(expected.begin(), expected.end( ), UPLEFT );

    vector<direction> actual = ourTank.findShortestPath(endCoords, Map, status);

    REQUIRE ( actual == expected );
}







