#include <iostream>
#include <string>
#include <vector>

int main()
{
   long long f0;
   long long n;
   std::cin >> f0 >> n; std::cin.ignore();
   long long a;
   long long b;
   std::cin >> a >> b; std::cin.ignore();

   std::vector<long long> years(n + 1, 0);
   years[0] = f0;
   for (long long year = 1; year < years.size(); ++year)
   {
      for (long long i = a; i <= b; ++i)
      {
         years[year] += year - i < 0 ? 0 : years[year - i];
      }
   }

   std::cout << years.back() << std::endl;
}
