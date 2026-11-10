#include <iostream>
#include <limits>
#include <vector>

typedef std::vector<std::vector<int>> Grid;

struct Vector2
{
   int x;
   int y;
};

class Starship
{
public:
   Starship(const Vector2& size, int shots) : size(size), shots(shots) {}

   int findMinShotsToLand(const Grid& grid)
   {
      int min_shots = -1;
      for (int i = 0; i < grid.size(); ++i)
      {
         for (int j = 0; j < grid[i].size(); ++j)
         {
            Vector2 land_position = Vector2{ j, i };
            int shots = getShotsToLand(size, land_position, grid);
            if (shots != -1 && (shots < min_shots || min_shots == -1))
            {
               min_shots = shots;
            }
            //sideaway
            shots = getShotsToLand(Vector2{size.y, size.x}, land_position, grid);
            if (shots != -1 && (shots < min_shots || min_shots == -1))
            {
               min_shots = shots;
            }
         }
      }
      return min_shots;
   }

private:
   int getShotsToLand(const Vector2& size, const Vector2& land, const Grid& grid)
   {
      int shots = 0;
      int min_height = std::numeric_limits<int>::max();
      for (int i = 0; i < size.y; ++i)
      {
         for (int j = 0; j < size.x; ++j)
         {
            if (land.y + i >= grid.size() || land.x + j >= grid[i].size())
            {
               return -1;
            }

            if (grid[land.y + i][land.x + j] < min_height)
            {
               min_height = grid[land.y + i][land.x + j];
            }
         }
      }

      for (int i = 0; i < size.y; ++i)
      {
         for (int j = 0; j < size.x; ++j)
         {
            shots += grid[land.y + i][land.x + j] - min_height;
         }
      }
      return shots;
   }

   Vector2 size;
   int shots;
};

int main()
{
   int w;
   int h;
   std::cin >> w >> h; std::cin.ignore();
   Grid grid;
   for (int i = 0; i < h; i++)
   {
      grid.push_back(std::vector<int>());
      for (int j = 0; j < w; j++)
      {
         int mountain_height;
         std::cin >> mountain_height; std::cin.ignore();
         grid[i].push_back(mountain_height);
      }
   }
   int a;
   int b;
   std::cin >> a >> b; std::cin.ignore();
   int t;
   std::cin >> t; std::cin.ignore();
   
   Starship starship(Vector2{ a, b }, t);
   int shots = starship.findMinShotsToLand(grid);
   if (shots == -1 || shots > t)
   {
      std::cout << "Not Possible" << std::endl;
   }
   else
   {
      std::cout << shots << std::endl;
   }
}
