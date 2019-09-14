#include "EasyEight.h"
/*************************************************//*
 * @author Riley Campbell
 * @par Description:
 * This is the constructor for the EasyEight class
 **************************************************/
EasyEight::EasyEight() {}


/***************************************************//**
 * @author Riley Campbell
 * @par Description:
 * This is the deconstructor for the EasyEight class
 ******************************************************/
EasyEight::~EasyEight() {}

/*********************************************************************//**
*   @author Logan Larson
*
*   @description: Makes a heap of the closest unvisited points.
*
*   @param[in] map - The current state of the playfield
*   @param[in] status - The AI's tank's location, health and ID
*
*************************************************************************/
void EasyEight::initToVisitList(MapData map, PositionData status)
{   

    int stepx = ceil((map.width/2.0)/myStats.tankRadar);
    int stepy;
    for ( int x = 0; x < map.width ; x+=stepx )
    {
        if( x + stepx >= map.width && stepx > 1)
            stepx--;
        
        stepy = ceil((map.height/2.0)/myStats.tankRadar - 0);
        for ( int y = 0; y < map.height; y+=stepy)
        {
            if( y + stepy >= map.height && stepy > 1)
            stepy--;

            if(myMap[x + map.width*y] == 0)
            {
                pointDistance nextPoint;
                nextPoint.x = x;
                nextPoint.y = y;
                
                
                nextPoint.path = findShortestPath({nextPoint.x,nextPoint.y}, map ,status); 

                toVisit.push_back(nextPoint);
            }
        }
    }    
}



/********************************************************************//**
*   @author Logan Larsen
*   
*   @description: Basically for the move interface. It calles other 
*                 functions to calculat its move.
*   
*   @return direction to move
*
************************************************************************/
direction EasyEight::move( MapData map, PositionData status )
{

    direction ret = STAY;

    if (myMap.empty() || toVisit.size() == 0 )
    {
        setMyMap( map, status );
    }
    
    if(toVisit.size() == 0)
        initToVisitList(map, status);
    

    updateMap( map, status);
    
    
    ret = moveToUnvisited(map, status);
    
    return ret;
}

/********************************************************************//**
*   @author Logan Larsen
*   
*   @description: Compares to distances as to which one is shorter
*   
*   @return true/false
*
************************************************************************/
bool compare(pointDistance lhs, pointDistance rhs)
{
    if(lhs.path.empty())
        return false;
    else if(rhs.path.empty())
        return true;

    //if paths are the same, compare points
    if(lhs.path.size() == rhs.path.size())
    {
        if(lhs.x== rhs.x)
            return lhs.y < rhs.y;
        else 
            return lhs.x < rhs.x;
    }
    
    return lhs.path.size() < rhs.path.size();
}
/********************************************************************//**
*   @author Logan Larsen
*   
*   @description: Finds a point on the map that we havent been to, and
*                 and returns a direction to get there
*   
*   @return direction
*
************************************************************************/
direction EasyEight::moveToUnvisited(MapData map,PositionData status)
{

    //create random points to move to    
    int nextx = 0;
    int nexty = 0;

    if ( status.game_x == nextx && status.game_y == nexty )
    {
        nextx = 1;
        nexty = 1;
    }    
    

    //update shortest paths
    for(unsigned int i = 0; i < toVisit.size(); i++)
    { 
        //v.path.clear();
        toVisit.at(i).path = findShortestPath({toVisit.at(i).x,toVisit.at(i).y}, map, status);
    }
    sort(toVisit.begin(), toVisit.end(), compare);

    vector<direction> dir = findShortestPath({nextx,nexty},map,status);
    if(!dir.empty() && toVisit.begin()->path.front() < 9)
    {

        return toVisit.begin()->path.front();
    }
    
    else
    {
        return STAY;
    }
    
}


/**************************************************************************//**
*   @author Nate Fagrey
*   
*   @desciption: This function finds the shortest path given end coords. 
*                The algorithm to do this is a little hairy, so stick with it. 
*
*   @return vector of directions to that endCoord
******************************************************************************/
vector<direction> EasyEight::findShortestPath ( pair<int, int> endCoords, 
    MapData Map, PositionData status )
{
    int root = 0, node = 0, start = 0, stop = 0;
    queue<int> Q;
    map<int, vector<direction>> expectedPath; 

    //1 = visited, 0 = not visited, -1 = do not go there!
    vector<int> visited(Map.height*Map.width);
    int adjacentNode;
    int j = -1;
    int k = 0;

    vector<direction> retDirections;

    //get root
    for ( int i = 0; i < Map.height * Map.width; ++i )
    {   
        if (Map.map[i] == status.id)
        {    
            root = i;

            visited[i] = 1; 
        }

        else if ( myMap[i] != 'W' && myMap[i] != 'R' )
            visited[i] = 0;

        //We are not going to count water or rocks as part of the graph
        else
            visited[i] = -1;
    }            



    //push root on Queue
    Q.push(root);

    //Start of BFS
    while ( !Q.empty() )
    { 
        
        node = Q.front();

        Q.pop();
    
    //this means we are on a left edge
    if ( node % Map.width == 0 )
    {
        start = 0;
        stop  = 2;   
    }

    //we are on a right edge
    else if ( node % Map.width == Map.width - 1)
    {
        start = -1;
        stop = 1;
    }

    //default
    else
    {
        start = -1;
        stop = 2;
    }

    j = -1;
    
    for( k = start; k < stop ; ++k )
    {
        //Adjdacent nodes algorithm
        adjacentNode = node + ( j * Map.width ) + k;

        //Have not visited
        if ( ( adjacentNode < Map.height * Map.width ) && ( visited[adjacentNode] == 0 ) 
            && (adjacentNode >= 0 ) && adjacentNode != node )
        {
            visited[adjacentNode] = 1;
            
            //store the path of node into the adjacentNode
            expectedPath[adjacentNode] = expectedPath[node];

            //add a direction to the path.
            expectedPath[adjacentNode].push_back(determineNextMove(j,k));

            Q.push(adjacentNode);
        }

            //sets up k and j so we get every adjacent node
            if ( k == stop  - 1 )
            {
                ++j;
                
                k = start  - 1; //Has to be one less than -1 ( our for loop will  fix it to -1 )
            }

            //we have reached the end
            if ( j > 1 )
              k = stop;
        }
    }


    int target = endCoords.first + endCoords.second * Map.width;

    //find the vector of directions that correspond to that target
    retDirections = expectedPath[target];

    //return that array that has the paths  
    return retDirections;
}
/*********************************************************************//**
*   @author Nathaniel Fagrey
*
*   @description: This function will determine and the next move we will
*                 need to take to get the adjacent node. 
*
*   @return direction
*************************************************************************/
direction EasyEight::determineNextMove( int j, int k)
{
    //row above current node
    if ( j == -1)
    {
        if ( k == 0 )
            return UP;

        if ( k == 1 )
            return UPRIGHT;

        if ( k == -1 )
            return UPLEFT;
    }

    //row that we are on    
    if ( j == 0 )
    {
        if ( k == 1 )
            return RIGHT;

        if ( k == -1 )
            return LEFT;
    }

    //row below the node that we are on    
    if ( j == 1 )
    {
        if ( k == 0 )
            return DOWN;

        if ( k == -1 )
            return DOWNLEFT;

        if ( k == 1 )
            return DOWNRIGHT;
    }

    //just to make the compiler happy, we will never actually return this
    return STAY;
}

/****************************************************************//*
 * @author Nathaniel Fagrey
 * 
 * @par Description: Runs through what we can see and keeping track
 *                   of all enemies that we have seen. It then calls
 *                   other functions to decide if and how to attack   
 * 
 * @return Location to attack and whether to attack
 *****************************************************************/
direction EasyEight::attack( MapData map, PositionData status )
{
    int x, y;

    pair<int, int> closestEnemy;
    
    direction ret = STAY;
    
    std::map<pair<int,int>, int> enemies;

    moveDir = STAY;


    //curret min distance to a target
    int distToTarget = map.width * map.height + 1;    
    
    //fill map with all enemies and their distance from our tanks postion
    for ( x = 0; x < map.width; ++x )  
        for ( y = 0; y < map.height; ++y )
            if ( map.map[x + y * map.width] //if there is an actor at X, y
                && map.map[x + y * map.width] != status.id  )
            {
                enemies[{x, y}] = calcDist(status.game_x, x, status.game_y, y);

                if ( enemies[{x, y}] < distToTarget )
                {
                      distToTarget = enemies[{x,y}];

                      closestEnemy = {x,y};
                }
            }
    

    //There are enemies, they arent too many, and they are on a straight or diagonal line from our tank...
    if ( enemies.size() != 0 && enemies.size() < TOOMANY  && 
    clearShot( closestEnemy.first, status.game_x, closestEnemy.second, status.game_y ) )
    {
        ret = getAttackDir( status.game_x, closestEnemy.first, status.game_y, closestEnemy.second );

        //moveDir = evade( status, closestEnemy, map );
    }

    //if not in a perfect situation...
    else
        ret = contingencyPlan( closestEnemy, enemies, map, status ); 
    
    

    return ret;
}

/***********************************************************************************************//**
*   @author Nathaniel Fagrey
*
*   @description Finds an alternate attack plan based on the gamefield and targets
*
*   @return direction
*
**************************************************************************************************/
direction EasyEight::contingencyPlan ( pair<int,int> closestEnemy, map<pair<int,int>, int> enemies, 
    MapData map, PositionData status )
{
    direction ret = STAY;

    moveDir = STAY;

    std::map<pair<int,int>, int>::iterator it;
    
    //This will make us move for a new enemy
    if ( enemies.size() == 0 )
        return STAY;
    
    //if we can't get the nearest one, just randomly go through the other ones until a clear shot is found
    else if ( enemies.size() < TOOMANY )
    {
        for (it = enemies.begin(); it != enemies.end(); ++it )
        {
            if ( clearShot( it->first.first, status.game_x, it->first.second, status.game_y ) )
            {   
                //moveDir = evade( status, it->first, map );
                
                return getAttackDir ( status.game_x, it->first.first, status.game_y, it->first.second );
            }
        
            //We do not have a clear shot
            else
            {
                ret = STAY;
            }
        }
    }

    else 
    {
        //FIXME!! This will be evade!
        ret = STAY;

        //moveDir = evade( status, closestEnemy, map );
    }

    return ret;
}

/*************************************************************************//**
*  @author Nathaniel Fagrey
*
*  @description returns direction to shoot based on the location of enemy
*
*  @return direction
****************************************************************************/
direction EasyEight::getAttackDir (int game_x, int x, int game_y, int y )
{
    direction ret = STAY;

     
    if ( game_x == x )
        ret = ( y > game_y ) ? DOWN : UP;

    else if ( game_y == y )
        ret = ( x > game_x ) ? RIGHT : LEFT;

    else if ( game_x > x ) //to the upright or downright
        ret = ( y > game_y ) ? DOWNLEFT : UPLEFT;

    else
        ret = ( y > game_y ) ? DOWNRIGHT : UPRIGHT;

    return ret;
}

/************************************************************************//**
*  @author Riley Campbell
*   
*  @description This function determines if a target is in a straight line 
*               from our tank ( diagonal or on the same x, y lines ) 
*   
*  @return true/false
*
****************************************************************************/
bool EasyEight::clearShot ( int x, int game_x, int y, int game_y )
{
    //straight formula
    int m = atan2(abs(y-game_y) , abs(x-game_x))*180/M_PI;

    if ( m == 0 || m == 90 || m == 45 )  
        return true;
    return false;

}


/***********************************************************************//**
 * @author Riley Cambell
 * @par Description:
 * Returns the attributes for the tank
 * @param[in] pointsAvailable - available points for the distribution
 * @return attributes of the tank
 ***************************************************************************/
attributes EasyEight::setAttribute( int pointsAvailable, attributes baseStats )
{
    attributes pointOffset;

    myStats = baseStats;


    while ( pointsAvailable > 0 )
    {
        ++myStats.tankAP;
        ++pointOffset.tankAP;
        --pointsAvailable;

        if ( pointsAvailable > 0 )
        {    ++myStats.tankDamage;
             ++pointOffset.tankDamage;
             --pointsAvailable;

             ++myStats.tankRadar;
             ++pointOffset.tankRadar;
             --pointsAvailable;

             ++myStats.tankRange;
             ++pointOffset.tankRange;
             --pointsAvailable;
        }
    }
    
    return pointOffset;
}

/******************************************************************//**
 * @author Christy Bergevin
 * @par Description: 
 * Updates our map with the current radar information
 *********************************************************************/
void EasyEight::updateMap( MapData map, PositionData status)
{
    int y = 0;
    int x = 0;
    int leftRadar = status.game_x - myStats.tankRadar;
    int rightRadar = status.game_x + myStats.tankRadar;
    int upRadar = status.game_y + myStats.tankRadar;
    int downRadar = status.game_y - myStats.tankRadar;

    if (leftRadar < 0)
        leftRadar = 0;
    if (rightRadar >= map.width)
        rightRadar = map.width - 1;
    if (downRadar < 0)
        downRadar = 0;
    if (upRadar >= map.height)
        upRadar = map.height - 1;

    for (x = leftRadar; x <= rightRadar; x++)
    {
        for (y = downRadar; y <= upRadar; y++)
        {
            if (myMap[x + y*map.width] == 0)
            {
                myMap[x + y*map.width] = 120;
                
                for(vector<pointDistance>::iterator v = toVisit.begin(); v != toVisit.end(); v++)
                {
                    if( !toVisit.empty() && v->x == x && v->y ==y)
                    {
                        toVisit.erase(v);
                        v--;
                    }
                }
            }
        }
    }

    for (x = leftRadar; x <= rightRadar; x++)
    {
        for (y = downRadar; y <= upRadar; y++)
        {
            if (map.obstacleMap[x + y*map.width] != 0)
            {
                myMap[x + y*map.width] = map.obstacleMap[x + y*map.width];
            }
            if (map.map[x + y*map.width] > 0)
                myMap[x + y*map.width] = map.map[x+ y*map.width];

        }
    }
}

/**********************************************************************//**
 * @author Christy Bergevin
 * @par Description: 
 * Prints myMap for debugging and testing purposes. Appears flipped (top to 
 * bottom) from GUI
 *************************************************************************/
void EasyEight::printMyMap(MapData map)
{
  std::cout << "My Map: \n";

    int size = (int)myMap.size();
    for (int i = 0; i < size; i++)
    {
        if (myMap[i] > 50)
            std::cout << (char)myMap[i];
        else
            std::cout << myMap[i];
        if (i % map.width == map.width - 1)
              printf("\n");
    }
}

/***********************************************************//*
 *  @author Nathaniel Fagrey
 * 
 *  @desciption: This function just initializes our map
 * 
 *  @return void
 *  
 ************************************************************/
void EasyEight::setMyMap( MapData map, PositionData status )
{       
    myMap.resize(map.width * map.height);
    std::fill(myMap.begin(), myMap.end(), 0);
    updateMap( map, status);
}

/********************************************************************//**
 * @author Logan Larsen
 * @par Description:
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] x1 - starting point x coordinate
 * @param[in] y1 - starting point y coordinate
 * @param[in] x2 - end point x coordinate
 * @param[in] y2 - end point y coordinate
 * @return distance to the target
 ************************************************************************/
int EasyEight::calcDist( int x1, int x2, int y1, int y2 )
{
    return  sqrt( pow( x1 - x2 ,2.0) + pow( y1 - y2 ,2.0) );
}

/*********************************************************************//**
*   @author Logan Larson
*
*   @description: Decides how we are going to spend our action points
*
*   @return choice
*************************************************************************/

int EasyEight::spendAP( MapData map, PositionData status )
{
    

    direction tMove = move( map, status );
    direction tAttack = attack( map, status );
    

    if (tAttack != STAY ) //If there is nowhere to move, attack
    {
        return ATTACK;
    }

    if ( tAttack == STAY && tMove != STAY ) //If there is nowhere to attack, move
        return MOVE;

    if ( tAttack == STAY && tMove == STAY ) //If there is nothing to do, end your turn
        return ENDTURN;

    //keep compiler happy...we will never actaully get here
    return ATTACK;
}


/********************************************************************//**
 * @author Riley Campbell
 * @par Description:
 * evades a dangerous position
 * @param[in] status - the status of our tank
 * @param[in] enemy - a pair of (x, y) coordinants for the enemy tank 
 * @param[in] map - the battle map
 * @return direction to evade to
 ************************************************************************/
  direction EasyEight::evade(PositionData status, pair<int, int> enemy, MapData map)
  {
     
      direction dir[3][3] = { {UPLEFT, LEFT, DOWNLEFT}, {UP, STAY, DOWN}, {UPRIGHT, RIGHT, DOWNRIGHT}};
      vector<direction> clear;
      pair <int, int> goTo;
      int  x, y, 
          EasyX = status.game_x,
          EasyY = status.game_y,
          enemyX = enemy.first,
          enemyY = enemy.second,
          theta = atan2(abs(EasyY - enemyY), abs(EasyX - enemyX)) * 180 / M_PI,
          Xoffset = 1 - EasyX,
          Yoffset = 1 - EasyY;
          bool found = false;

        //check if already safe
        if( theta != 0 && theta != 45 && theta != 90)
        {          
            evadeDir = STAY;
            return evadeDir;
        }
        //find a safe location to evade to
        for ( x = -1 + EasyX; x < 2 + EasyX && !found; x++)
        {
            for(y = -1 + EasyY; y < 2 + EasyY && !found; y++)
            {
                if(x >= 0 &&  x < map.width && y >= 0 && y < map.height)
                {                    
                    theta = atan2(abs(y - enemyY), abs(x- enemyX)) * 180 / M_PI;
                    if( theta != 0 && theta != 45 && theta != 90)
                    { 
                        if(!map.map[x + y * map.width]) 
                        {                   
                            evadeDir = dir[x - EasyX + Xoffset][y - EasyY + Yoffset];
                            found = true;
                        }
                    }  
                }   
            } 
        }
   
    return evadeDir;
  }

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new EasyEight;
    }
}
#endif
