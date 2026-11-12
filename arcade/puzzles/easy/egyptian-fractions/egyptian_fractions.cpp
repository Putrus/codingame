#include <iostream>
#include <string>
#include <cmath>

long long gcd(long long a, long long b)
{
   while (b != 0)
   {
      long long temp = b;
      b = a % b;
      a = temp;
   }
   return a;
}

int main()
{
   std::string rational;
   getline(std::cin, rational);

   long long p = stoll(rational.substr(0, rational.find('/')));
   long long q = stoll(rational.substr(rational.find('/') + 1));
   long long g = gcd(p, q);
   p /= g;
   q /= g;

   long long k = 1;
   while (p * k > q)
   {
      std::cout << "1/" << k << " + ";

      p = p * k - q;
      q = q * k;

      g = gcd(p, q);
      p /= g;
      q /= g;

      k++;
   }


   while (p != 1)
   {
      long long k = ceil((double)q / p);
      std::cout << "1/" << k << " + ";
      p = p * k - q;
      q = q * k;

      g = gcd(p, q);
      p /= g;
      q /= g;
   }
   std::cout << p << "/" << q;
}
