#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Position
{
   int x;
   int y;
};

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
   os << '(' << pos.x << ", " << pos.y << ')';
   return os;
}

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<std::string> grid;
   std::vector<std::string> empty_grid;
   for (int i = 0; i < n; i++)
   {
      std::string m;
      std::cin >> m; std::cin.ignore();
      grid.push_back(m);
      empty_grid.push_back(std::string(m.size(), '-'));
   }

   for (int i = 0; i < grid.size(); ++i)
   {
      for (int j = 0; j < grid[i].size(); ++j)
      {
         if (grid[i][j] == 'a')
         {
            Position pos = { j, i };
            std::vector<std::string> result_grid = empty_grid;
            char next_letter = grid[pos.y][pos.x];
            while (true)
            {
               result_grid[pos.y][pos.x] = next_letter;
               std::cerr << "Letter: " << next_letter << " " << pos << std::endl;
               if (next_letter == 'z')
               {
                  for (const auto& row : result_grid)
                  {
                     std::cout << row << std::endl;
                  }
               }
               next_letter = grid[pos.y][pos.x] + 1;
               if (pos.x > 0 && grid[pos.y][pos.x - 1] == next_letter)
               {
                  std::cerr << "Left" << std::endl;
                  --pos.x;
               }
               else if (pos.x < grid[pos.y].size() - 1 && grid[pos.y][pos.x + 1] == next_letter)
               {
                  std::cerr << "Right" << std::endl;
                  ++pos.x;
               }
               else if (pos.y > 0 && grid[pos.y - 1][pos.x] == next_letter)
               {
                  std::cerr << "Up" << std::endl;
                  --pos.y;
               }
               else if (pos.y < grid.size() - 1 && grid[pos.y + 1][pos.x] == next_letter)
               {
                  std::cerr << "Down" << std::endl;
                  ++pos.y;
               }
               else
               {
                  break;
               }
            }
         }
      }
   }
}