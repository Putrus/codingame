#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start, int goal)
{
   int n = graph.size();

   std::vector<bool> visited(n, false);
   std::vector<int> parent(n, -1);
   std::queue<int> q;

   q.push(start);
   visited[start] = true;

   while (!q.empty())
   {
      int v = q.front();
      q.pop();

      if (v == goal)
         break;

      for (int neighbour : graph[v])
      {
         if (!visited[neighbour])
         {
            visited[neighbour] = true;
            parent[neighbour] = v;
            q.push(neighbour);
         }
      }
   }

   // path not found
   if (!visited[goal])
      return {};

   std::vector<int> path;
   for (int v = goal; v != -1; v = parent[v])
   {
      path.push_back(v);
   }

   reverse(path.begin(), path.end());

   return path;
}

int main()
{
   int n; // the total number of nodes in the level, including the gateways
   int l; // the number of links
   int e; // the number of exit gateways
   std::cin >> n >> l >> e; std::cin.ignore();
   std::vector<std::vector<int>> graph(n);
   for (int i = 0; i < l; i++)
   {
      int n1; // N1 and N2 defines a link between these nodes
      int n2;
      std::cin >> n1 >> n2; std::cin.ignore();
      graph[n1].push_back(n2);
      graph[n2].push_back(n1);
   }
   std::vector<int> gateways;
   for (int i = 0; i < e; i++)
   {
      int ei; // the index of a gateway node
      std::cin >> ei; std::cin.ignore();
      gateways.push_back(ei);
   }

   // game loop
   while (true)
   {
      int si; // The index of the node on which the Bobnet agent is positioned this turn
      std::cin >> si; std::cin.ignore();
      std::cerr << si << std::endl;

      std::vector<int> best_path;
      for (int gateway : gateways)
      {
         auto path = bfs(graph, si, gateway);
         if (best_path.empty() || (!path.empty() && path.size() < best_path.size()))
         {
            best_path = std::move(path);
         }
      }
      int node0 = best_path[best_path.size() - 2];
      int node1 = best_path.back();
      std::cout << node0 << " " << node1 << std::endl;
      graph[node0].erase(std::remove(graph[node0].begin(),
         graph[node0].end(), node1), graph[node0].end());
      graph[node1].erase(std::remove(graph[node1].begin(),
         graph[node1].end(), node0), graph[node1].end());
   }
}
