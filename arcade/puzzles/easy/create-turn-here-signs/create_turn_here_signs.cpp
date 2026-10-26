#include <iostream>
#include <string>
#include <sstream>

int main()
{
   std::string input;
   getline(std::cin, input);
   std::stringstream ss(input);
   std::string direction;
   int n;
   int height;
   int stroke;
   int spacing;
   int indent;
   ss >> direction >> n >> height >> stroke >> spacing >> indent;

   if (direction == "right")
   {
      for (int h = 0; h < height; ++h)
      {
         for (int i = 0; i < n; ++i)
         {
            if (i == 0)
            {
               if (h <= height / 2)
               {
                  for (int in = 0; in < h * indent; ++in)
                  {
                     std::cout << ' ';
                  }
               }
               else
               {
                  for (int in = 0; in < height * indent - (h + 1) * indent; ++in)
                  {
                     std::cout << ' ';
                  }
               }
            }
            else
            {
               for (int s = 0; s < spacing; ++s)
               {
                  std::cout << ' ';
               }
            }

            for (int s = 0; s < stroke; ++s)
            {
               std::cout << '>';
            }
         }
         std::cout << std::endl;
      }
   }
   else
   {
      for (int h = 0; h < height; ++h)
      {
         for (int i = 0; i < n; ++i)
         {
            if (i == 0)
            {
               if (h <= height / 2)
               {
                  for (int in = 0; in < (height / 2) * indent - h * indent; ++in)
                  {
                     std::cout << ' ';
                  }
               }
               else
               {
                  for (int in = 0; in < h * indent - (height / 2) * indent; ++in)
                  {
                     std::cout << ' ';
                  }
               }
            }
            else
            {
               for (int s = 0; s < spacing; ++s)
               {
                  std::cout << ' ';
               }
            }

            for (int s = 0; s < stroke; ++s)
            {
               std::cout << '<';
            }
         }
         std::cout << std::endl;
      }
   }
}