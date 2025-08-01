#include <iostream>
#include <string>

std::string toBinary(char c)
{
   std::string binary;
   while (c != 0)
   {
      if (c % 2 == 0)
      {
         binary = "0" + binary;
      }
      else
      {
         binary = "1" + binary;
      }
      c /= 2;
   }

   while (binary.size() < 7)
   {
      binary = "0" + binary;
   }
   return binary;
}

int main()
{
   std::string message;
   std::getline(std::cin, message);

   char series = 'x';
   for (char c : message)
   {
      std::string binary = toBinary(c);
      for (char bit : binary)
      {
         if (bit != series)
         {
            if (series != 'x')
            {
               std::cout << ' ';
            }
            series = bit;
            if (series == '1')
            {
               std::cout << "0 0";
            }
            else
            {
               std::cout << "00 0";
            }
         }
         else
         {
            std::cout << '0';
         }
      }
   }
}