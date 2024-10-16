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

struct Position
{
   int x;
   int y;

   Position& operator+=(const Position& other)
   {
      this->x += other.x;
      this->y += other.y;
      return *this;
   }
};

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
   os << "(" << pos.x << ", " << pos.y << ")";
   return os;
}

bool operator==(const Position& lhs, const Position& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Position& lhs, const Position& rhs)
{
   return lhs.x != rhs.x || lhs.y != rhs.y;
}

Position find(char id, const std::vector<std::string>& grid)
{
   for (int i = 0; i < grid.size(); ++i)
   {
      for (int j = 0; j < grid[i].size(); ++j)
      {
         if (grid[i][j] == id)
         {
            return { j, i };
         }
      }
   }
   return { -1, -1 };
}

int main()
{
   int h;
   int w;
   std::cin >> h >> w; std::cin.ignore();
   std::vector<std::string> result(h, std::string(w, ' '));
   std::vector<std::string> grid;
   for (int i = 0; i < h; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      grid.push_back(row);
   }


   Position first = find('1', grid);

   char id = '2';
   Position second = find(id, grid);
   while (second.x != -1)
   {
      result[first.y][first.x] = 'o';
      Position dir = { 0, 0 };
      dir.x = first.x == second.x ? 0 : first.x > second.x ? -1 : 1; 
      dir.y = first.y == second.y ? 0 : first.y > second.y ? -1 : 1;

      char sign = '-';
      if (dir.x == 0)
      {
         sign = '|';
      }
      else if (dir.y == 0)
      {
         sign = '-';
      }
      else if (dir.x == dir.y)
      {
         sign = '\\';
      }
      else
      {
         sign = '/';
      }

      Position pos = first;
      pos += dir;
      while (pos != second)
      {
         if (result[pos.y][pos.x] == ' ')
         {
            result[pos.y][pos.x] = sign;
         }
         else if (result[pos.y][pos.x] == '-')
         {
            if (sign == '|')
            {
               result[pos.y][pos.x] = '+';
            }
            else if (sign == '/' || sign == '\\')
            {
               result[pos.y][pos.x] = '*';
            }
         }
         else if (result[pos.y][pos.x] == '|')
         {
            if (sign == '-')
            {
               result[pos.y][pos.x] = '+';
            }
            else if (sign == '/' || sign == '\\')
            {
               result[pos.y][pos.x] = '*';
            }
         }
         else if (result[pos.y][pos.x] == '/')
         {
            if (sign == '\\')
            {
               result[pos.y][pos.x] = 'X';
            }
            else if (sign == '-' || sign == '|')
            {
               result[pos.y][pos.x] = '*';
            }
         }
         else if (result[pos.y][pos.x] == '\\')
         {
            if (sign == '/')
            {
               result[pos.y][pos.x] = 'X';
            }
            else if (sign == '-' || sign == '|')
            {
               result[pos.y][pos.x] = '*';
            }
         }
         else if (result[pos.y][pos.x] == 'X')
         {
            if (sign == '-' || sign == '|')
            {
               result[pos.y][pos.x] = '*';
            }
         }
         else if (result[pos.y][pos.x] == '+')
         {
            if (sign == '\\' || sign == '/')
            {
               result[pos.y][pos.x] = '*';
            }
         }
         pos += dir;
      }
      first = second;
      if (id == '9')
      {
         id = 'A';
      }
      else
      {
         ++id;
      }
      second = find(id, grid);
   }

   result[first.y][first.x] = 'o';

   for (auto& row : result)
   {
      rtrim(row);
      std::cout << row << std::endl;
   }
}