#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void rtrim(std::string& str)
{
   str.erase(std::find_if(str.rbegin(), str.rend(),
      [](unsigned char ch)
      {
         return !std::isspace(ch);
      }).base(), str.end());
}

void trimAndDisplayGrid(std::vector<std::string>& grid)
{
   if (grid.empty())
   {
      return;
   }

   size_t min_leading_spaces = grid[0].size();

   for (const auto& row : grid)
   {
      auto it = std::find_if(row.begin(), row.end(),
         [](unsigned char ch)
         {
            return !std::isspace(ch);
         });

      if (it != row.end())
      {
         size_t leading_spaces = std::distance(row.begin(), it);
         min_leading_spaces = std::min(min_leading_spaces, leading_spaces);
      }
   }

   for (auto& row : grid)
   {
      if (row.size() >= min_leading_spaces)
      {
         row.erase(0, min_leading_spaces);
      }
      rtrim(row);
      if (row.size() == 0)
      {
         continue;
      }
      std::cout << row << std::endl;
   }
}

struct Position
{
   int x;
   int y;
};

void addRectangle(const Position& position, std::vector<std::string>& grid, const std::vector<std::string>& rectangle)
{
   if (position.x < 1 || position.x + 1 >= grid[0].size() || position.y < 0 || position.y + 1 >= grid.size())
   {
      return;
   }
   grid[position.y][position.x - 1] = rectangle[0][0];
   grid[position.y][position.x] = rectangle[0][1];
   grid[position.y][position.x + 1] = rectangle[0][2];
   grid[position.y + 1][position.x - 1] = rectangle[1][0];
   grid[position.y + 1][position.x] = rectangle[1][1];
   grid[position.y + 1][position.x + 1] = rectangle[1][2];
}

int main()
{
   std::string message;
   getline(std::cin, message);

   std::vector<std::string> grid(500, std::string(500, ' '));

   Position position = { grid.size() / 2, grid.size() / 2 };

   if (message.empty())
   {
      return 0;
   }

   char last_dir = message[0];
   if (last_dir == 'D')
   {
      addRectangle(position, grid,
         { "+-+",
           "| |" });
      position.y += 2;
   }
   else if (last_dir == 'L')
   {
      addRectangle(position, grid,
         { "--+",
           "--+" });
      position.x -= 3;
   }
   else if (last_dir == 'R')
   {
      addRectangle(position, grid,
         { "+--",
           "+--" });
      position.x += 3;
   }
   else
   {
      addRectangle(position, grid,
         { "| |",
           "+-+" });
      position.y -= 2;
   }

   for (int i = 1; i < message.size(); ++i)
   {
      char dir = message[i];
      if (dir == 'D')
      {
         if (last_dir == 'D')
         {
            addRectangle(position, grid,
               { "| |",
                 "| |" });
         }
         else if (last_dir == 'L')
         {
            addRectangle(position, grid,
               { "+--",
                 "| +" });
         }
         else if (last_dir == 'R')
         {
            addRectangle(position, grid,
               { "--+",
                 "+ |" });
         }

         position.y += 2;
      }
      else if (dir == 'U')
      {
         if (last_dir == 'U')
         {
            addRectangle(position, grid,
               { "| |",
                 "| |" });
         }
         else if (last_dir == 'L')
         {
            addRectangle(position, grid,
               { "| +",
                 "+--" });
         }
         else if (last_dir == 'R')
         {
            addRectangle(position, grid,
               { "+ |",
                 "--+" });
         }

         position.y -= 2;
      }
      else if (dir == 'L')
      {
         if (last_dir == 'L')
         {
            addRectangle(position, grid,
               { "---",
                 "---" });
         }
         else if (last_dir == 'U')
         {
            addRectangle(position, grid,
               { "--+",
                 "+ |" });
         }
         else if (last_dir == 'D')
         {
            addRectangle(position, grid,
               { "+ |",
                 "--+" });
         }

         position.x -= 3;
      }
      else if (dir == 'R')
      {
         if (last_dir == 'R')
         {
            addRectangle(position, grid,
               { "---",
                 "---" });
         }
         else if (last_dir == 'U')
         {
            addRectangle(position, grid,
               { "+--",
                 "| +" });
         }
         else if (last_dir == 'D')
         {
            addRectangle(position, grid,
               { "| +",
                 "+--" });
         }

         position.x += 3;
      }

      last_dir = dir;
   }

   if (last_dir == 'R')
   {
      addRectangle(position, grid,
         { "--+",
           "--+" });
   }
   else if (last_dir == 'U')
   {
      addRectangle(position, grid,
         { "+-+",
           "| |" });
   }
   else if (last_dir == 'D')
   {
      addRectangle(position, grid,
         { "| |",
           "+-+" });
   }
   else
   {
      addRectangle(position, grid,
         { "+--",
           "+--" });
   }

   trimAndDisplayGrid(grid);
}