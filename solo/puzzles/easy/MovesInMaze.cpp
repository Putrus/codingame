#include <iostream>
#include <string>
#include <stack>
#include <vector>

struct Position
{
   int x;
   int y;
};

bool operator==(const Position& lhs, const Position& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y;
}

int main()
{
   int w;
   int h;
   std::vector<std::string> maze;
   std::cin >> w >> h; std::cin.ignore();
   Position start;
   for (int i = 0; i < h; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      maze.push_back(row);
      for (int j = 0; j < row.size(); ++j)
      {
         if (row[j] == 'S')
         {
            start.x = j;
            start.y = i;
         }
      }
   }

   std::stack<std::pair<Position, int>> to_visit;
   
   to_visit.push({ start, 0 });
   while (!to_visit.empty())
   {
      auto pos = to_visit.top();
      to_visit.pop();
      maze[pos.first.y][pos.first.x] = pos.second >= 10 ? pos.second + 'A' - 10 : pos.second + '0';

      int new_x = (pos.first.x - 1 + maze[pos.first.y].size()) % maze[pos.first.y].size();
      if (maze[pos.first.y][new_x] == '.' ||
         maze[pos.first.y][new_x] > maze[pos.first.y][pos.first.x] + 1)
      {
         to_visit.push({ { pos.first.x - 1, pos.first.y }, pos.second + 1 });
      }

      if (maze[(pos.first.y - 1 + maze.size()) % maze.size()][pos.first.x] == '.' ||
         maze[(pos.first.y - 1 + maze.size()) % maze.size()][pos.first.x] > maze[pos.first.y][pos.first.x] + 1)
      {
         to_visit.push({ { pos.first.x, pos.first.y - 1 }, pos.second + 1 });
      }

      if (maze[pos.first.y][(pos.first.x + 1) % maze[pos.first.y].size()] == '.' ||
         maze[pos.first.y][(pos.first.x + 1) % maze[pos.first.y].size()] > maze[pos.first.y][pos.first.x] + 1)
      {
         to_visit.push({ { pos.first.x + 1, pos.first.y }, pos.second + 1 });
      }

      if (maze[(pos.first.y + 1) % maze.size()][pos.first.x] == '.' ||
         maze[(pos.first.y + 1) % maze.size()][pos.first.x] > maze[pos.first.y][pos.first.x] + 1)
      {
         to_visit.push({ { pos.first.x, pos.first.y + 1 }, pos.second + 1 });
      }

      for (const auto& row : maze)
      {
         std::cerr << row << std::endl;
      }
      std::cerr << std::endl;
   }

   for (const auto& row : maze)
   {
      std::cout << row << std::endl;
   }
}