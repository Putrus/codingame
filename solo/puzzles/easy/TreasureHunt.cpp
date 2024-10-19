#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

struct Position
{
   int x;
   int y;
};

int main()
{
   int h;
   int w;
   std::cin >> h >> w; std::cin.ignore();
   std::vector<std::string> grid;
   std::vector<std::vector<int>> result_grid(h, std::vector(w, 0));

   Position pos = { -1, -1, }; 
   for (int i = 0; i < h; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      grid.push_back(row);
      if (pos.x != -1)
      {
         continue;
      }
      for (int j = 0; j < row.size(); ++j)
      {
         if (row[j] == 'X')
         {
            pos = { j, i };
         }
      }
   }

   std::stack<std::pair<Position, Position>> positions;
   positions.push({ { -1, -1 }, pos });
   while (!positions.empty())
   {
      auto position = positions.top();
      positions.pop();
      if (grid[position.second.y][position.second.x] == '#')
      {
         continue;
      }

      if (position.first.x == -1)
      {
         result_grid[position.second.y][position.second.x] = grid[position.second.y][position.second.x];
      }
      else
      {
         int new_value = result_grid[position.first.y][position.first.x] + (grid[position.second.y][position.second.x] - '0');
         if (new_value > result_grid[position.second.y][position.second.x])
         {
            result_grid[position.second.y][position.second.x] = new_value;
            if (position.second.x > 0)
            {
               positions.push({ position.second, { position.second.x - 1, position.second.y } });
            }

            if (position.second.x < w - 1)
            {
               positions.push({ position.second, { position.second.x + 1, position.second.y } });
            }

            if (position.second.y > 0)
            {
               positions.push({ position.second, { position.second.x, position.second.y - 1} });
            }

            if (position.second.y < h - 1)
            {
               positions.push({ position.second, { position.second.x, position.second.y + 1 } });
            }
         }
      }

      for (const auto& row : result_grid)
      {
         for (int val : row)
         {
            std::cerr << val;
         }
         std::cerr << std::endl;
      }
   }
}