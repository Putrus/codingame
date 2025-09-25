#include <iostream>
#include <string>

long long digitsSum(const std::string& str)
{
   long long sum = 0;
   for (char c : str)
   {
      sum += static_cast<long long>(c - '0');
   }
   return sum;
}

int main()
{
   long long r_1, r_2;
   std::cin >> r_1 >> r_2; std::cin.ignore();
   
   while (r_1 != r_2)
   {
      if (r_1 < r_2)
      {
         r_1 += digitsSum(std::to_string(r_1));
      }
      else
      {
         r_2 += digitsSum(std::to_string(r_2));
      }      
   }
   
   std::cout << r_1 << std::endl;
}
