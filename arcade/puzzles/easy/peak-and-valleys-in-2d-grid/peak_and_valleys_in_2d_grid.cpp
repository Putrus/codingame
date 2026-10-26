#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Vec2
{
   int x;
   int y;
};

std::ostream& operator<<(std::ostream& os, const Vec2& vec)
{
   os << '(' << vec.x << ", " << vec.y << ')';
   return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Vec2>& vec)
{
   if (vec.empty())
   {
      os << "NONE";
   }
   for (int i = 0; i < vec.size(); ++i)
   {
      os << vec[i];
      if (i != vec.size() - 1)
      {
         os << ", ";
      }
   }
   return os;
}

class CellClassifier
{
public:
   CellClassifier(const std::vector<std::vector<int>>& grid) : grid(grid) {}

   bool isPeak(int x, int y)
   {
      int height = grid[y][x];
      return isLower(x - 1, y, height) &&
         isLower(x - 1, y - 1, height) &&
         isLower(x, y - 1, height) &&
         isLower(x + 1, y - 1, height) &&
         isLower(x + 1, y, height) &&
         isLower(x + 1, y + 1, height) &&
         isLower(x, y + 1, height) &&
         isLower(x - 1, y + 1, height); 
   }

   bool isValley(int x, int y)
   {
      int height = grid[y][x];
      return isHigher(x - 1, y, height) &&
         isHigher(x - 1, y - 1, height) &&
         isHigher(x, y - 1, height) &&
         isHigher(x + 1, y - 1, height) &&
         isHigher(x + 1, y, height) &&
         isHigher(x + 1, y + 1, height) &&
         isHigher(x, y + 1, height) &&
         isHigher(x - 1, y + 1, height);
   }

private:
   bool isOffTheGrid(int x, int y)
   {
      return y < 0 || y == grid.size() || x < 0 || x == grid[y].size();
   }

   bool isHigher(int x, int y, int height)
   {
      return isOffTheGrid(x, y) || grid[y][x] > height;
   }

   bool isLower(int x, int y, int height)
   {
      return isOffTheGrid(x, y) || grid[y][x] < height;
   }

   std::vector<std::vector<int>> grid;
};

int main()
{
   int h;
   std::cin >> h; std::cin.ignore();
   std::vector<std::vector<int>> grid; 
   for (int i = 0; i < h; i++)
   {
      std::vector<int> row;
      std::string line;
      std::getline(std::cin, line);
      std::stringstream ss(line);
      while (!ss.eof())
      {
         int height;
         ss >> height;
         row.push_back(height);
      }
      grid.push_back(row);
   }

   CellClassifier classifier(grid);

   std::vector<Vec2> peaks;
   std::vector<Vec2> valleys;
   for (int i = 0; i < grid.size(); ++i)
   {
      for (int j = 0; j < grid[i].size(); ++j)
      {
         if (classifier.isPeak(j, i))
         {
            peaks.push_back({ j, i });
         }
         else if (classifier.isValley(j, i))
         {
            valleys.push_back({ j, i });
         }
      }
   }
   
   std::cout << peaks << std::endl << valleys; 
}
