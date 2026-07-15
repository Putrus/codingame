#include <iostream>
#include <string>

int main()
{
   std::string b;
   std::getline(std::cin, b);

   long long longest = 0;

   for (int i = 0; i < b.size(); ++i)
   {
      if (b[i] == '0')
      {
         long long ones = 1;
         // left
         for (int j = i - 1; j >= 0; --j)
         {
            if (b[j] == '1')
               ++ones;
            else
               break;
         }

         // right
         for (int j = i + 1; j < b.size(); ++j)
         {
            if (b[j] == '1')
               ++ones;
            else
               break;
         }
         if (ones > longest)
            longest = ones;
      }
   }

   std::cout << longest << std::endl;
}
