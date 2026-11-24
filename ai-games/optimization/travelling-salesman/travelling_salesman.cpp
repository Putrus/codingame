#include <iostream>
#include <vector>

int main()
{
   int n;
   std::cin >> n;

   std::vector<int> x(n);
   std::vector<int> y(n);

   for (int i = 0; i < n; ++i)
   {
      std::cin >> x[i] >> y[i];
   }

   std::vector<bool> visited(n, false);
   std::vector<int> path;

   int current = 0;

   path.push_back(0);
   visited[0] = true;

   for (int step = 1; step < n; ++step)
   {
      int nearest = -1;
      double best_distance = std::numeric_limits<double>::max();

      for (int i = 0; i < n; ++i)
      {
         if (visited[i])
         {
            continue;
         }

         int dx = x[current] - x[i];
         int dy = y[current] - y[i];

         double distance = dx * dx + dy * dy;

         if (distance < best_distance)
         {
            best_distance = distance;
            nearest = i;
         }
      }

      current = nearest;
      visited[current] = true;
      path.push_back(current);
   }

   // back to start position
   path.push_back(0);

   for (int i = 0; i < static_cast<int>(path.size()); ++i)
   {
      if (i > 0)
      {
         std::cout << ' ';
      }

      std::cout << path[i];
   }

   std::cout << std::endl;
}
