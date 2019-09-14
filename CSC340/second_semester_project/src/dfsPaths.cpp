#include "dfsPaths.h"

DFSPaths::DFSPaths(Graph *G, int v) : s(v)
{
   dist[s] = 0;
   dfs(G, s); 
}

bool DFSPaths::hasPathTo(int v)
{
   return marked[v];
}

int DFSPaths::distance(int v)
{
   return dist[v];
}

std::list<int> DFSPaths::pathTo(int v)
{
   std::list<int> path;
   if (!hasPathTo(v)) return path;
   for (int x = v ; x != s ; x = prev[x])
      path.push_front(x);
   path.push_front(s);
   return path;
}

void DFSPaths::dfs(Graph *G, int v)
{
   marked[v] = true;
   for (int w : G->adj(v))
   {
      if (!marked[w])
      {
         dfs(G, w);
         prev[w] = v; 
         dist[w] = dist[v] + 1;
      }
   }
}
