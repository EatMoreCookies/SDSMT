#include "Sentry.h"
#include <iostream>

Sentry::Sentry() : lastMove(STAY), repeatCounter(0)
{
   srand(time(NULL));
}

Sentry::~Sentry() {}

void buildDirectionMap(MapData &map, int range, std::map<int, direction> &directionMap)
{
   for (int dist = 1 ; dist <= range ; dist++)
   {
      directionMap[-1*dist] = LEFT;
      directionMap[1*dist]  = RIGHT;
      directionMap[map.width*dist] = DOWN;
      directionMap[-map.width*dist] = UP;
      directionMap[map.width*dist+dist] = DOWNRIGHT;
      directionMap[-map.width*dist+dist] = UPRIGHT;
      directionMap[map.width*dist-dist] = DOWNLEFT;
      directionMap[-map.width*dist-dist] = UPLEFT;
   }
}

bool validMove(MapData &map, int me, direction nextStep)
{
   if (nextStep == STAY) return false;
   int Row = me / map.width;
   int Col = me % map.width;

   Row += moveDirection[nextStep].first;
   Col += moveDirection[nextStep].second;
 
   if (!validRow(Row) || !validCol(Col) || !validCell(Row, Col)) return false;
   return true;
}

direction Sentry::move(MapData map, PositionData status)
{
    int myPosition = status.game_x + status.game_y * map.width;

    direction nextMove = lastMove;
    while (!validMove(map, myPosition, nextMove))
       nextMove = dirs[rand() % 9];

    lastMove = nextMove;
    return nextMove;
}

direction Sentry::attack(MapData map, PositionData status)
{
   int me = status.game_x + status.game_y * map.width;
   std::map<int,int>::iterator firstThreat = threats.begin();
   int threat = (*firstThreat).first;

   direction shotDirection = directionMap[threat-me];

   if (lastMe == me && lastShotDirection == shotDirection)
      repeatCounter++;
   else
   {
      lastMe = me;
      lastShotDirection = shotDirection;
   }
   return shotDirection;
}

attributes Sentry::setAttribute(int pointsAvailable, attributes baseStats)
{
   attributes tankAttributes;
  
   myAttributes = baseStats;
   myAttributes.tankRange += pointsAvailable; 
   tankAttributes.tankRange += pointsAvailable;

   return tankAttributes;
}

bool Sentry::threatDetected(MapData &map, PositionData &status)
{
   threats.clear();
   int me = status.game_y * map.width + status.game_x;
   for (int row = Max(0, status.game_y - myAttributes.tankRange) ;
            row < Min(status.game_y + myAttributes.tankRange, map.height) ;
            row++)
      for (int col = Max(0, status.game_x - myAttributes.tankRange) ;
               col < Min(status.game_y + myAttributes.tankRange, map.width) ;
               col++)
      {
         int index = row * map.width + col;
         int cell = map.map[index];
         if (cell == status.id || cell == -status.id) continue;
         if (((cell > 0 && cell <= 9) || (cell < 0 && cell >= -9)) &&
             (directionMap.find(index-me) != directionMap.end()))
            threats[index] = cell;
      }
   return (threats.size() > 0);
}

int Sentry::attackOrMove(MapData &map, PositionData &status)
{
   if (threatDetected(map, status) && repeatCounter < REPEAT_LIMIT)
      return ATTACK;

   repeatCounter = 0;
   return MOVE;
}

int Sentry::spendAP(MapData map, PositionData status)
{
    if (directionMap.size() == 0) buildDirectionMap(map, myAttributes.tankRange, directionMap);

    return attackOrMove(map, status);
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new Sentry;
    }
}
#endif
