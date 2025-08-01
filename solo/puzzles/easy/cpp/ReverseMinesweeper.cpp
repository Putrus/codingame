#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int w;
   std::cin >> w; std::cin.ignore();
   int h;
   std::cin >> h; std::cin.ignore();

   std::vector<std::vector<int>> win_grid;
   std::vector<std::string> bomb_grid;
   for (int i = 0; i < h; i++)
   {
      std::string line;
      std::getline(std::cin, line);
      bomb_grid.push_back(line);
      std::vector<int> win_line(w, 0);
      win_grid.push_back(win_line);
   }

   for (int y = 0; y < h; ++y)
   {
      for (int x = 0; x < w; ++x)
      {
         if (bomb_grid[y][x] == 'x')
         {
            if (y > 0)
            {
               if (x > 0 && bomb_grid[y - 1][x - 1] != 'x')
               {
                  ++win_grid[y - 1][x - 1];
               }

               if (bomb_grid[y - 1][x] != 'x')
               {
                  ++win_grid[y - 1][x];
               }

               if (x + 1 < w && bomb_grid[y - 1][x + 1] != 'x')
               {
                  ++win_grid[y - 1][x + 1];
               }
            }

            if (x > 0 && bomb_grid[y][x - 1] != 'x')
            {
               ++win_grid[y][x - 1];
            }

            if (x + 1 < w && bomb_grid[y][x + 1] != 'x')
            {
               ++win_grid[y][x + 1];
            }

            if (y + 1 < h)
            {
               if (x > 0 && bomb_grid[y + 1][x - 1] != 'x')
               {
                  ++win_grid[y + 1][x - 1];
               }

               if (bomb_grid[y + 1][x] != 'x')
               {
                  ++win_grid[y + 1][x];
               }

               if (x + 1 < w && bomb_grid[y + 1][x + 1] != 'x')
               {
                  ++win_grid[y + 1][x + 1];
               }
            }
         }
      }
   }

   for (const auto& row : win_grid)
   {
      for (int value : row)
      {
         if (value == 0)
         {
            std::cout << '.';
         }
         else
         {
            std::cout << value;
         }
      }
      std::cout << std::endl;
   }
}