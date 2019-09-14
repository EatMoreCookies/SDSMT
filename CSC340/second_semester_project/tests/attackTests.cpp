#include"../src/EasyEight.h"
#include"../src/MapData.h"
#include"../src/PositionData.h"
#include"../src/SimpleAI.h"
#include "catch.hpp"

TEST_CASE ( "Return DOWNRIGHT")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[24] = 2;
    enemyPos.id = 2;


    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == DOWNRIGHT);
}


TEST_CASE ( "Return UP")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[2] = 2;
    enemyPos.id = 2;
 
    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == UP);
}

TEST_CASE ( "Return DOWN")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[22] = 2;
    enemyPos.id = 2;

    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == DOWN);
}


TEST_CASE ( "Return DOWNLEFT")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[20] = 2;
    enemyPos.id = 2;

    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == DOWNLEFT);
}

TEST_CASE ( "Return UPLEFT")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[0] = 2;
    enemyPos.id = 2;

    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == UPLEFT);
}

TEST_CASE ( "Return UPRIGHT")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[4] = 2;
    enemyPos.id = 2;

    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == UPRIGHT);
}


TEST_CASE ( "Return LEFT")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[10] = 2;
    enemyPos.id = 2;

    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == LEFT);
}


TEST_CASE ( "Return RIGHT")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[12] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[14] = 2;
    enemyPos.id = 2;

    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == RIGHT);
}


TEST_CASE ( "Return STAY if no targets")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[0] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 0;
    ourTankPos.game_y = 0; 


    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == STAY);
}



/*TEST_CASE ( "If one of our enemies is on a staight line but the closest one is not" )
{
    PositionData ourTankPos;
    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    attributes baseStats;


    Map.map[24] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 4;
    ourTankPos.game_y = 4; 

    Map.map[17] = 2;
    Map.map[4] = 3;

    ourTank.setAttribute( 10, baseStats );

    ourTank.setMyMap( Map, ourTankPos );


    attack = ourTank.attack(Map, ourTankPos);

    
    REQUIRE( attack == UP);
}*/


TEST_CASE ( "If one of our enemies is closer than the other one")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[24] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 4;
    ourTankPos.game_y = 4; 

    Map.map[18] = 2;

    Map.map[4] = 3;


    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == UPLEFT);
}



/*TEST_CASE ( "return STAY if target not in a straight line")
{
    PositionData ourTankPos;
    PositionData enemyPos;

    direction attack;

    MapData Map(5, 5);

    EasyEight ourTank;

    SimpleAI enemy;


    Map.map[4] = 1; 
    ourTankPos.id = 1;
    ourTankPos.game_x = 2;
    ourTankPos.game_y = 2; 

    Map.map[19] = 2;



    attack = ourTank.attack(Map, ourTankPos);
    
    REQUIRE( attack == STAY);
}*/





