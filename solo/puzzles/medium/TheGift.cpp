#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   int c;
   std::cin >> c; std::cin.ignore();

   std::vector<std::pair<int, int>> participants;
   participants.reserve(n);
   for (int i = 0; i < n; i++)
   {
      int b;
      std::cin >> b; std::cin.ignore();
      participants.push_back({ b, 0 });
   }

   int full_budgets = 0;
   while (c > 0 && full_budgets != participants.size())
   {
      full_budgets = 0;
      for (auto& participant : participants)
      {
         if (participant.first == participant.second)
         {
            ++full_budgets;
            continue;
         }

         --c;
         ++participant.second;

         if (c == 0)
            break;
      }
   }

   if (c > 0)
   {
      std::cout << "IMPOSSIBLE" << std::endl;
   }
   else
   {
      std::sort(participants.begin(), participants.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs.second < rhs.second;
         });
      for (const auto& participant : participants)
      {
         std::cout << participant.second << std::endl;
      }
   }
}