#include <iostream>
#include <vector>
#include <string>

struct Vec2
{
   int x;
   int y;
};

bool inGrid(const std::vector<std::string>& grid, const Vec2& position)
{
   return position.x >= 0 && position.y >= 0 && position.y < grid.size() && position.x < grid[position.y].size();
}

Vec2 turnLeft(const Vec2& direction)
{
   return { direction.y, -direction.x };
}

Vec2 turnRight(const Vec2& direction)
{
   return { -direction.y, direction.x };
}

int main()
{
   int h, w;
   std::cin >> h >> w;
   std::cin.ignore();
   std::vector<std::string> grid;
   for (int i = 0; i < h; i++)
   {
      std::string row;
      getline(std::cin, row);
      grid.push_back(row);
   }

   Vec2 position = { 0, 0 };
   Vec2 direction = { 1, 0 };
   int steps = 1;
   std::string path;
   while (true)
   {
      Vec2 new_position = position;
      new_position.x += direction.x;
      new_position.y += direction.y;

      if (!inGrid(grid, new_position) || grid[new_position.y][new_position.x] == '.')
      {
         Vec2 left_direction = turnLeft(direction);
         Vec2 left_position = position;
         left_position.x += left_direction.x;
         left_position.y += left_direction.y;
         if (inGrid(grid, left_position) && grid[left_position.y][left_position.x] == '#')
         {
            path += std::to_string(steps);
            path += "L";
            steps = 0;
            direction = std::move(left_direction);
            continue;
         }

         Vec2 right_direction = turnRight(direction);
         Vec2 right_position = position;
         right_position.x += right_direction.x;
         right_position.y += right_direction.y;
         if (inGrid(grid, right_position) && grid[right_position.y][right_position.x] == '#')
         {
            path += std::to_string(steps);
            path += "R";
            steps = 0;
            direction = std::move(right_direction);
            continue;
         }
         path += std::to_string(steps);
         break;
      }
      else
      {
         ++steps;
         position = std::move(new_position);
      }
   }

   std::cout << path << std::endl;
}
