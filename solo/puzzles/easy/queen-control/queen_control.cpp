#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Point
{
   int x;
   int y;
};

int checkControl(const std::vector<std::string> board, Point position, Point step, Point max, const std::string& color)
{
   int controlled = 0;
   position.y += step.y;
   position.x += step.x;
   while (position.y != max.y && position.x != max.x)
   {
      char square = board[position.y][position.x];
      if (square == 'Q')
      {
         return controlled;
      }

      if (square == '.')
      {
         ++controlled;
      }
      else if ((color == "white" && square == 'w') ||
         (color == "black" && square == 'b'))
      {
         return controlled;
      }
      else
      {
         return ++controlled;
      }
      position.y += step.y;
      position.x += step.x;
   } 
   return controlled;
}

int main()
{
   std::string color;
   std::getline(std::cin, color);
   std::vector<std::string> board;
   Point queenPos = { 0, 0 };    
   for (int i = 0; i < 8; i++)
   {
      std::string line;
      std::getline(std::cin, line);
      board.push_back(line);

      for (int j = 0; j < line.size(); ++j)
      {
         if (line[j] == 'Q')
         {
            queenPos = { j, i };
         }
      }
   }

   int max_int = std::numeric_limits<int>::max();
   int controlled = 0;
   controlled += checkControl(board, queenPos, { 1, 0 }, { static_cast<int>(board.size()), max_int }, color);
   controlled += checkControl(board, queenPos, { 1, 1 }, { static_cast<int>(board.size()), static_cast<int>(board[0].size()) }, color);
   controlled += checkControl(board, queenPos, { 0, 1 }, { max_int, static_cast<int>(board[0].size()) }, color);
   controlled += checkControl(board, queenPos, { -1, 1 }, { -1, static_cast<int>(board[0].size()) }, color);
   controlled += checkControl(board, queenPos, { -1, 0 }, { -1, max_int }, color);
   controlled += checkControl(board, queenPos, { -1, -1 }, { -1, -1 }, color);
   controlled += checkControl(board, queenPos, { 0, -1 }, { max_int, -1 }, color);
   controlled += checkControl(board, queenPos, { 1, -1 }, { static_cast<int>(board.size()), -1 }, color);
   std::cout << controlled << std::endl;
}
