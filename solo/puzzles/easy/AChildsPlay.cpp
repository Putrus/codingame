#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Position
{
   int x;
   int y;
   long long moves;
};

bool operator==(const Position& lhs, const Position& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y;
}

Position operator+(const Position& lhs, const Position& rhs)
{
   return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.moves + rhs.moves };
}

int main()
{
   int w;
   int h;
   std::cin >> w >> h; std::cin.ignore();
   long long n;
   std::cin >> n; std::cin.ignore();
   std::vector<std::string> map;
   Position current_pos;
   for (int i = 0; i < h; i++)
   {
      std::string line;
      std::getline(std::cin, line);
      map.push_back(line);
      for (int j = 0; j < line.size(); ++j)
      {
         if (line[j] == 'O')
         {
            current_pos = { j, i, 0 };
         }
      }
   }

   std::vector<Position> history;

   Position dir = { 0, -1, 1 };
   while (current_pos.moves < n)
   {
      if (std::find(history.begin(), history.end(), current_pos) != history.end())
      {
         n %= current_pos.moves;
         current_pos.moves = 0;
         history.clear();
      }
      history.push_back(current_pos);
      Position new_pos = current_pos + dir;
      if (map[new_pos.y][new_pos.x] == '#')
      {
         if (dir.x != 0)
         {
            dir.y = dir.x;
            dir.x = 0;
         }
         else if (dir.y != 0)
         {
            dir.x = -dir.y;
            dir.y = 0;
         }
      }
      map[current_pos.y][current_pos.x] = '.';
      current_pos = current_pos + dir;
      map[current_pos.y][current_pos.x] = 'O';

      for (const auto& row : map)
      {
         std::cerr << row << std::endl;
      }
      std::cerr << std::endl;
   }

   std::cout << current_pos.x << " " << current_pos.y << std::endl;
}