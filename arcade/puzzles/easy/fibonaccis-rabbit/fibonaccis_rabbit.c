#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
   long long F0;
   long long N;
   scanf("%lld%lld", &F0, &N);
   long long a;
   long long b;
   scanf("%lld%lld", &a, &b);

   long long* years = malloc((N + 1) * sizeof(long long));
   years[0] = F0;
   for (long long i = 1; i <= N; ++i)
   {
      years[i] = 0;
      for (long long j = a; j <= b; ++j)
      {
         if (i - j >= 0)
         {
            years[i] += years[i - j];
         }
      }
   }

   printf("%lld", years[N]);

   return 0;
}
