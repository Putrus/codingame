#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <array>

struct Point
{
   int x = 0;
   int y = 0;
};

constexpr std::array<Point, 4> directions = {
   Point{ 0, -1 },
   Point{ 1, 0 },
   Point{ 0, 1 },
   Point{ -1, 0 }
};

struct Cell : public Point
{
   int gold = 0;
};

class TreasureHunter
{
public:
   TreasureHunter(const std::vector<std::string>& grid, const Point& start_pos)
      : grid(grid), start_pos(start_pos) {}

   int hunt() const
   {
      std::stack<std::pair<Cell, std::vector<Point>>> positions;
      positions.push({ { start_pos.x, start_pos.y, 0 }, {} });

      int gold = 0;
      while (!positions.empty())
      {
         auto [current, path] = positions.top();
         positions.pop();

         if (grid[current.y][current.x] == '#')
         {
            continue;
         }

         if (current.gold > gold)
         {
            gold = current.gold;
         }

         path.push_back(current);
         for (const auto& dir : directions)
         {
            Point new_position = { current.x + dir.x, current.y + dir.y };
            if (std::find_if(path.begin(), path.end(), [&new_position](const Point& point)
               {
                  return point.x == new_position.x && point.y == new_position.y;
               }) != path.end())
            {
               continue;
            }
            if (isValidPosition(new_position))
            {
               positions.push({ { new_position.x, new_position.y, current.gold +
                  (grid[new_position.y][new_position.x] == ' ' ? 0 : grid[new_position.y][new_position.x] - '0') }, path });
            }
         }
      }
      return gold;
   }

private:
   bool isValidPosition(const Point& p) const
   {
      return p.x >= 0 && p.x < grid[0].size() && p.y >= 0 && p.y < grid.size() && grid[p.y][p.x] != '#';
   }

   std::vector<std::string> grid;
   Point start_pos;
};

int main()
{
   int h;
   int w;
   std::cin >> h >> w; std::cin.ignore();
   std::vector<std::string> grid;
   std::vector<std::vector<int>> result_grid(h, std::vector(w, 0));

   Point start_pos = { -1, -1 }; 
   for (int i = 0; i < h; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      grid.push_back(row);
      if (start_pos.x != -1)
      {
         continue;
      }
      for (int j = 0; j < row.size(); ++j)
      {
         if (row[j] == 'X')
         {
            start_pos = { j, i };
         }
      }
   }

   TreasureHunter hunter(grid, start_pos);
   std::cout << hunter.hunt() << std::endl;
}