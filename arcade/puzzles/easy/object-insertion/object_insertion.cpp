#include <iostream>
#include <string>
#include <vector>

bool fit(int i, int j, const std::vector<std::string>& object, const std::vector<std::string>& grid)
{
   for (int y = 0; y < object.size(); ++y)
   {
      for (int x = 0; x < object[y].size(); ++x)
      {
         int y_pos = i + y;
         int x_pos = j + x;
         if (object[y][x] == '*' && (y_pos >= grid.size() || x_pos >= grid[y_pos].size() || grid[y_pos][x_pos] == '#'))
         {
            return false;
         }
      }
   }
   return true;
}

int main()
{
   int a;
   int b;
   std::cin >> a >> b; std::cin.ignore();
   std::vector<std::string> object;
   for (int i = 0; i < a; i++)
   {
      std::string object_line;
      std::getline(std::cin, object_line);
      object.push_back(object_line);
   }
   int c;
   int d;
   std::cin >> c >> d; std::cin.ignore();
   std::vector<std::string> grid;
   for (int i = 0; i < c; i++)
   {
      std::string grid_line;
      std::getline(std::cin, grid_line);
      grid.push_back(grid_line);
   }

   int ways = 0;
   std::vector<std::string> first_way;
   for (int i = 0; i < grid.size(); ++i)
   {
      for (int j = 0; j < grid.size(); ++j)
      {
         if (fit(i, j, object, grid))
         {
            ++ways;

            if (first_way.empty())
            {
               first_way = grid;
               for (int y = 0; y < object.size(); ++y)
               {
                  for (int x = 0; x < object[y].size(); ++x)
                  {
                     if (object[y][x] == '*')
                     {
                        first_way[i + y][j + x] = '*';
                     }
                  }
               }
            }
         }
      }
   }

   std::cout << ways << std::endl;
   if (ways == 1)
   {
      for (const auto& row : first_way)
      {
         std::cout << row << std::endl;
      }
   }
}