#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

constexpr int GRID_SIZE = 10;

struct Position
{
   int x;
   int y;
};

bool operator==(const Position& lhs, const Position& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y;
}

Position findPos(const std::vector<std::string>& grid, const std::vector<Position>& valid)
{
   int start = grid.size() / 2 - 1;
   int size = 2;
   for (int i = start; i >= 0; --i, size += 2)
   {
      for (int y = 0; y < size; ++y)
      {
         for (int x = 0; x < size; ++x)
         {
            if (grid[i + y][i + x] == '.')
            {
               if (std::find(valid.begin(), valid.end(), Position{i + y, i + x}) != valid.end())
               {
                  return { i + y, i + x };
               }
            }
         }
      }
   }
   return { -1, -1 };
}

bool isFull(const std::vector<std::string>& grid)
{
   for (auto& row : grid)
   {
      for (char c : row)
      {
         if (c == '.')
         {
            return false;
         }
      }
   }
   return true;
}

void reset(std::vector<std::string>& grid)
{
   for (auto& row : grid)
   {
      for (auto& c : row)
      {
         c = '.';
      }
   }
}

int main()
{
   std::vector<std::string> grid;
   for (int i = 0; i < GRID_SIZE; ++i)
   {
      std::string row;
      for (int j = 0; j < GRID_SIZE; ++j)
      {
         row += ".";
      }
      grid.push_back(row);
   }

   // game loop
   while (1)
   {
      int opponent_row; // The coordinates of your opponent's last move
      int opponent_col;
      std::cin >> opponent_row >> opponent_col;
      if (opponent_row != -1)
      {
         grid[opponent_row][opponent_col] = 'o';
      }

      if (isFull(grid))
      {
         reset(grid);
      }

      std::cin.ignore();
      int valid_action_count; // the number of possible actions for your next move
      std::cin >> valid_action_count;
      std::cin.ignore();
      std::vector<Position> valid;
      for (int i = 0; i < valid_action_count; i++)
      {
         int row; // The coordinates of a possible next move
         int col;
         std::cin >> row >> col;
         std::cin.ignore();
         valid.push_back({ row, col });
      }

      Position pos = findPos(grid, valid);
      std::cout << pos.x << " " << pos.y << std::endl;
      grid[pos.x][pos.y] = 'x';

      if (isFull(grid))
      {
         reset(grid);
      }

      for (const auto& row : grid)
      {
         std::cerr << row << std::endl;
      }
   }
}