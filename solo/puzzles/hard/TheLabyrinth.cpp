#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int r; // number of rows.
   int c; // number of columns.
   int a; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
   std::cin >> r >> c >> a; std::cin.ignore();

   std::string last_move = "";
   // game loop
   while (1)
   {
      int kr; // row where Rick is located.
      int kc; // column where Rick is located.
      std::cin >> kr >> kc; std::cin.ignore();
      std::vector<std::string> maze;
      for (int i = 0; i < r; i++)
      {
         std::string row; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
         std::cin >> row; std::cin.ignore();
         maze.push_back(row);
         std::cerr << row << std::endl;
      }

      if (last_move == "RIGHT" || last_move == "")
      {
         if (maze[kr][kc + 1] == '.' || maze[kr][kc + 1] == 'C')
         {
            last_move = "RIGHT";
         }
         else if (maze[kr + 1][kc] == '.' || maze[kr + 1][kc] == 'C')
         {
            last_move = "DOWN";
         }
         else if (maze[kr - 1][kc] == '.' || maze[kr - 1][kc] == 'C')
         {
            last_move = "UP";
         }
         else
         {
            last_move = "LEFT";
         }
      }

      if (last_move == "LEFT")
      {
         if (maze[kr][kc - 1] == '.' || maze[kr][kc - 1] == 'C')
         {
            last_move = "LEFT";
         }
         else if (maze[kr + 1][kc] == '.' || maze[kr + 1][kc] == 'C')
         {
            last_move = "DOWN";
         }
         else if (maze[kr - 1][kc] == '.' || maze[kr - 1][kc] == 'C')
         {
            last_move = "UP";
         }
         else
         {
            last_move = "RIGHT";
         }
      }

      if (last_move == "UP" || last_move == "")
      {
         if (maze[kr - 1][kc] == '.' || maze[kr - 1][kc] == 'C')
         {
            last_move = "UP";
         }
         else if (maze[kr][kc + 1] == '.' || maze[kr][kc + 1] == 'C')
         {
            last_move = "RIGHT";
         }
         else if (maze[kr][kc - 1] == '.' || maze[kr][kc - 1] == 'C')
         {
            last_move = "LEFT";
         }
         else
         {
            last_move = "DOWN";
         }
      }

      if (last_move == "DOWN")
      {
         if (maze[kr + 1][kc] == '.' || maze[kr + 1][kc] == 'C')
         {
            last_move = "DOWN";
         }
         else if (maze[kr][kc + 1] == '.' || maze[kr][kc + 1] == 'C')
         {
            last_move = "RIGHT";
         }
         else if (maze[kr][kc - 1] == '.' || maze[kr][kc - 1] == 'C')
         {
            last_move = "LEFT";
         }
         else
         {
            last_move = "UP";
         }
      }

      std::cout << last_move << std::endl; // Rick's next move (UP DOWN LEFT or RIGHT).
   }
}