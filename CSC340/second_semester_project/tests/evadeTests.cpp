//evading tests
#include"../src/EasyEight.h"
#include"../src/MapData.h"
#include"../src/PositionData.h"
#include "catch.hpp"
//1
TEST_CASE ( "We are at (0,0), enemy is at (2,0), dont walk off map, and return DOWN" )
{ 
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords(2,0); 
    status.game_x = 0;
    status.game_y = 0;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir == DOWN);
}
TEST_CASE ( "If we are not in danger, return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;

    MapData map(3,3);
    attributes baseStats;
    baseStats.tankRadar = 10;
    ourTank.setAttribute( 10, baseStats ); 

    pair<int,int> enemyCoords (0, 0);    
    status.game_x = 1;
    status.game_y = 2;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir == STAY);
}
//2
TEST_CASE ( "We are at (1,1), enemy is at (0,0), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (0, 0);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//3
TEST_CASE ( "We are at (1,1), enemy is at (1,0), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (1, 0);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//4
TEST_CASE ( "We are at (1,1), enemy is at (2,0), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (2, 0);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//5
TEST_CASE ( "We are at (1,1), enemy is at (2,1), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (2, 1);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//6
TEST_CASE ( "We are at (1,1), enemy is at (2,2), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (2, 2);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//7
TEST_CASE ( "We are at (1,1), enemy is at (1,2), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (1, 2);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//8
TEST_CASE ( "We are at (1,1), enemy is at (0,2), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (0, 2);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//9
TEST_CASE ( "We are at (1,1), enemy is at (0,1), dont return STAY" )
{
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (0,1);    
    status.game_x = 1;
    status.game_y = 1;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir != STAY);
}
//10
TEST_CASE ( "We are at (0,0), enemy is at (1,1), dont walk off map, and return STAY" )
{   
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords (1,1);    
    status.game_x = 0;
    status.game_y = 0;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir == STAY);
}
/*
//11
TEST_CASE ( "We are at (0,0), enemy is at (2,0), dont walk off map, and return DOWN" )
{ 
    EasyEight ourTank;
    PositionData status;
    direction evadeDir;
    
    MapData map(3,3);

    pair<int,int> enemyCoords(2,0); 
    status.game_x = 0;
    status.game_y = 0;
   
    evadeDir = ourTank.evade (status, enemyCoords, map);

    REQUIRE ( evadeDir == DOWN);
}

   0,0    1,0    2,0

     0,1    1,1    2,1

     0,2    1,2    2,2
*/
