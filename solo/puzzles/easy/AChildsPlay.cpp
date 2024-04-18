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

bool operator==(const std::pair<Position, Position>& lhs, const std::pair<Position, Position>& rhs)
{
   return lhs.first == rhs.first && lhs.second == rhs.second;
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

   std::vector<std::pair<Position, Position>> history;

   Position dir = { 0, -1, 1 };
   while (current_pos.moves < n)
   {
      auto find = std::find(history.begin(), history.end(), std::pair<Position, Position>(current_pos, dir));
      if (find != history.end())
      {
         n = (n - find->first.moves) % (current_pos.moves - find->first.moves);
         current_pos.moves = 0;
         history.clear();
      }
      history.push_back({ current_pos, dir });
      Position new_pos = current_pos + dir;
      if (map[new_pos.y][new_pos.x] == '#')
      {
         std::swap(dir.x, dir.y);
         dir.x = -dir.x;
      }
      map[current_pos.y][current_pos.x] = '.';
      new_pos = current_pos + dir;
      if (map[new_pos.y][new_pos.x] == '#')
      {
         std::swap(dir.x, dir.y);
         dir.x = -dir.x;
      }
      current_pos = current_pos + dir;
      map[current_pos.y][current_pos.x] = 'O';
   }

   std::cout << current_pos.x << " " << current_pos.y << std::endl;
}