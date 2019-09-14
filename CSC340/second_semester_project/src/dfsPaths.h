#ifndef __DFSPATHS_H
#define __DFSPATHS_H
#include <list>
#include <map>
#include <vector>
#include "graph.h"

class DFSPaths
{
   map<int, bool> marked;
   map<int, int> prev;
   map<int, int> dist;
   int s;

public:
   DFSPaths(Graph *G, int s);

   void dfs(Graph *G, int s);
   bool hasPathTo(int v);
   std::list<int> pathTo(int v);
   int distance(int v);
};
#endif
