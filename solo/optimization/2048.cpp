#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   while (1)
   {
      int seed;
      std::cin >> seed; std::cin.ignore();
      int score;
      std::cin >> score; std::cin.ignore();
      for (int i = 0; i < 4; i++)
      {
         for (int j = 0; j < 4; j++)
         {
            int cell;
            std::cin >> cell; std::cin.ignore();
         }
      }

      int move = std::rand() % 4;
      char moves[5] = "ULRD";
      std::cout << moves[move] << std::endl;
   }
}