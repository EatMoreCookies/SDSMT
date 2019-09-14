#include "Turret.h"
#include <iostream>
#include <iomanip>
#include <cmath>

const direction dirs[] = 
   {
      UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, STAY
   };

Turret::Turret() {}
Turret::~Turret() {}

direction Turret::move(MapData map, PositionData status)
{
    return STAY;
}

direction threatDirection(int me, int threat, int width)
{
   int rowOffset = (threat / width) - (me / width); 
   int colOffset = (threat % width) - (me % width);
   
   if (rowOffset == 0) return (colOffset < 0) ? LEFT : RIGHT;
   if (colOffset == 0) return (rowOffset < 0) ? UP : DOWN;
   
   if (abs(rowOffset) == abs(colOffset))
   {
      if (rowOffset < 0 && colOffset < 0) return UPLEFT;
      if (rowOffset < 0 && colOffset > 0) return UPRIGHT;
      if (rowOffset > 0 && colOffset < 0) return DOWNLEFT;
      if (rowOffset > 0 && colOffset > 0) return DOWNRIGHT;
   }
   return STAY;
}

direction Turret::attack(MapData map, PositionData status)
{
   int me = status.game_x + status.game_y * map.width;
   // Prioritize killing of threats.  TODO:Upgrade by choosing the threat
   // that is shootable with the lowest health
   for (auto &kv : threats)
   {
      direction dir = threatDirection(me, kv.first, map.width);
      if (dir != STAY)
         return dir;
   }

   // If there are obstacles in range, clear them if possible
   for (auto &kv : obstacles)
   {
      direction dir = threatDirection(me, kv.first, map.width);
      if (dir != STAY) 
         return dir;
   }
   return STAY;
}

attributes Turret::setAttribute(int pointsAvailable, attributes baseStats)
{
   name = "Turret";
   while (pointsAvailable > 0)
   {
      if (baseStats.tankRange < baseStats.tankRadar)
      {
         baseStats.tankRange++;
         pointsAvailable--;
      } 
      else if (baseStats.tankRange > baseStats.tankRadar)
      {
         baseStats.tankRadar++;
         pointsAvailable--;
      }
      else if (pointsAvailable % 2 == 0)
      {
         baseStats.tankRange++;
         baseStats.tankRadar++;
         pointsAvailable -= 2;
      }
      else
      {
         baseStats.tankDamage++;
         pointsAvailable--;
      }
   }
       
   std::cout << "Tank Attributes:\n";
   std::cout << "Health: " << baseStats.tankHealth << std::endl;
   std::cout << "AP    : " << baseStats.tankAP     << std::endl;
   std::cout << "Damage: " << baseStats.tankDamage << std::endl;
   std::cout << "Radar : " << baseStats.tankRadar  << std::endl;
   std::cout << "Range : " << baseStats.tankRange  << std::endl;
   std::cout << "Ammo  : " << baseStats.tankAmmo   << std::endl;
   myAttributes = baseStats;
   return baseStats;
}

int calcDistance(int v, std::pair<int,int> me, int width)
{
   return abs(v%width-me.first)+abs(v/width-me.second);
}

bool Turret::threatDetected(MapData map, PositionData status)
{
   threats.clear();
   obstacles.clear();
   int me = status.game_x + status.game_y * map.width;
   
   for (int vertex = 0 ; vertex < map.height * map.width ; vertex++)
   {
      int cell = map.map[vertex];
      int distance = calcDistance(vertex, std::pair<int,int>(status.game_x,status.game_y), map.width);
      if (distance > myAttributes.tankRange || cell == status.id || cell == -status.id) continue;
      if ((cell > 0 && cell <= 9) || (cell < 0 && cell >= -9))
         if (threatDirection(me, vertex, map.width) != STAY)
            threats[vertex] = cell;
   }


   for (int vertex = 0 ; vertex < map.height * map.width ; vertex++)
   {
      int cell = map.obstacleMap[vertex];
      int distance = calcDistance(vertex, std::pair<int,int>(status.game_x,status.game_y), map.width);
      if (distance < myAttributes.tankRange && (cell == 'R' || cell == 'T' || cell == 'C'))
         if (threatDirection(me, vertex, map.width) != STAY)
            obstacles[vertex] = cell;
   }

   return (threats.size() > 0 || obstacles.size() > 0);
}

int Turret::spendAP(MapData map, PositionData status)
{
    return (threatDetected(map, status) ? ATTACK : RELOAD);
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new Turret;
    }
}
#endif
