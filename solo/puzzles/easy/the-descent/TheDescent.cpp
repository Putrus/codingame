#include <iostream>
#include <string>

int main()
{
   // game loop
   while (1)
   {
      int max = 0;
      int id = 0;
      for (int i = 0; i < 8; i++)
      {
         int mountain_h; // represents the height of one mountain.
         std::cin >> mountain_h; std::cin.ignore();
         if (mountain_h > max)
         {
            max = mountain_h;
            id = i;
         }
      }
      std::cout << id << std::endl; // The index of the mountain to fire on.
   }
}