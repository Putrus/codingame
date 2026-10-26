#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool checkRows(const std::vector<std::vector<int>>& grid)
{
   for (int i = 0; i < grid.size(); ++i)
   {
      std::vector<int> exists;
      for (int j = 0; j < grid[i].size(); ++j)
      {
         if (std::find(exists.begin(), exists.end(), grid[i][j]) == exists.end())
         {
            exists.push_back(grid[i][j]);
         }
         else
         {
            return false;
         }
      }
   }
   return true;
}

bool checkColumns(const std::vector<std::vector<int>>& grid)
{
   if (grid.empty())
   {
      return false;
   }

   for (int j = 0; j < grid[0].size(); ++j)
   {
      std::vector<int> exists;
      for (int i = 0; i < grid.size(); ++i)
      {
         if (std::find(exists.begin(), exists.end(), grid[i][j]) == exists.end())
         {
            exists.push_back(grid[i][j]);
         }
         else
         {
            return false;
         }
      }
   }
   return true;
}

bool checkSquares(const std::vector<std::vector<int>>& grid)
{
   for (int i = 0; i < grid.size(); i += 3)
   {
      for (int j = 0; j < grid[i].size(); j += 3)
      {
         std::vector<int> exists;
         for (int y = i; y < i + 3; ++y)
         {
            for (int x = j; x < j + 3; ++x)
            {
               if (std::find(exists.begin(), exists.end(), grid[y][x]) == exists.end())
               {
                  exists.push_back(grid[y][x]);
               }
               else
               {
                  return false;
               }
            }
         }
         
      }
   }
   return true;
}


int main()
{
   std::vector<std::vector<int>> grid;
   for (int i = 0; i < 9; i++)
   {
      grid.push_back(std::vector<int>());
      for (int j = 0; j < 9; j++)
      {
         int n;
         std::cin >> n; std::cin.ignore();
         grid[i].push_back(n);
      }
   }

   if (checkRows(grid) && checkColumns(grid) && checkSquares(grid))
   {
      std::cout << "true" << std::endl;
   }
   else
   {
      std::cout << "false" << std::endl;
   }
}