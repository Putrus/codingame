#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int thickness;
   std::cin >> thickness; std::cin.ignore();
   int length;
   std::cin >> length; std::cin.ignore();
   int turns;
   std::cin >> turns; std::cin.ignore();

   std::cout << ' ';
   char sign = ' ';
   for (int i = 0; i < turns + 1; ++i)
   {
      for (int j = 0; j < thickness; ++j)
      {
         std::cout << '_';
      }

      if (i == turns)
      {
         break;
      }

      std::cout << sign;
      if (sign == ' ')
      {
         sign = '_';
      }
      else
      {
         sign = ' ';
      }
   }
   std::cout << std::endl;

   sign = '|';
   std::cout << '|';
   for (int j = 0; j < turns + 1; ++j)
   {
      for (int k = 0; k < thickness; ++k)
      {
         std::cout << ' ';
      }

      if (j == turns)
      {
         break;
      }
      
      std::cout << sign;
      if (sign == ' ')
      {
         sign = '|';
      }
      else
      {
         sign = ' ';
      }
   }
   std::cout << '|' << std::endl;
   
   for (int i = 0; i < length - 2; ++i)
   {
      std::cout << '|';
      for (int j = 0; j < turns + 1; ++j)
      {
         for (int k = 0; k < thickness; ++k)
         {
            std::cout << ' ';
         }
         std::cout << '|';
      }
      std::cout << std::endl;
   }

   sign = '_';
   std::cout << '|';
   for (int j = 0; j < turns + 1; ++j)
   {
      for (int k = 0; k < thickness; ++k)
      {
         std::cout << '_';
      }

      if (j == turns)
      {
         break;
      }

      std::cout << sign;
      if (sign == '|')
      {
         sign = '_';
      }
      else
      {
         sign = '|';
      }
   }
   std::cout << '|' << std::endl;
}