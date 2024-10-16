#include <iostream>
#include <string>
#include <vector>

void rtrim(std::string& str) {
   str.erase(std::find_if(str.rbegin(), str.rend(),
   [](unsigned char ch)
   {
      return !std::isspace(ch);
   }).base(), str.end());
}

struct Position
{
   int x;
   int y;
};

void addRectangle(const Position& position, std::vector<std::string>& grid, const std::vector<std::string>& rectangle)
{
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

   std::vector<std::string> grid(150, std::string(150, ' '));

   Position position = { 1, 0 };
   addRectangle(position, grid,
      { "+-+",
        "| |" });
   position.y += 2;
   char last_dir = message[0];
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

   for (int i = 0; i < grid.size(); ++i)
   {
      rtrim(grid[i]);
      if (grid[i].size() == 0)
      {
         return 0;
      }
      std::cout << grid[i] << std::endl;
   }
}