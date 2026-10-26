#include <iostream>
#include <string>
#include <vector>

struct Group
{
   long long earning;
   int next_index;
};

int main()
{
   int l;
   int c;
   int n;
   std::cin >> l >> c >> n; std::cin.ignore();
   std::vector<int> queue(n);
   for (int i = 0; i < n; i++)
   {
      int pi;
      std::cin >> pi; std::cin.ignore();
      queue[i] = pi;
   }

   long long earnings = 0;
   int index = 0;
   int begin_index = 0;
   if (c < n)
   {
      for (int i = 0; i < c; ++i)
      {
         int space = l;
         begin_index = index;
         while (queue[index] <= space)
         {
            earnings += queue[index];
            space -= queue[index];
            index = (index + 1) % n;
            if (index == begin_index)
            {
               break;
            }
         }
      }
   }
   else
   {
      std::vector<Group> groups(n);
      for (int i = 0; i < n; ++i)
      {
         index = i;
         begin_index = index;
         int space = l;
         long long earning = 0;
         while (queue[index] <= space)
         {
            earning += queue[index];
            space -= queue[index];
            index = (index + 1) % n;
            if (index == begin_index)
            {
               break;
            }
         }

         groups[i] = { earning, index };
      }

      index = 0;
      for (int i = 0; i < c; ++i)
      {
         earnings += groups[index].earning;
         index = groups[index].next_index;
      }
   }

   std::cout << earnings << std::endl;
}