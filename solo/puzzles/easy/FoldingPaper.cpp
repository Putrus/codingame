#include <iostream>
#include <string>
#include <vector>
#include <map>

int main()
{
   std::string order;
   std::getline(std::cin, order);
   std::string side;
   std::getline(std::cin, side);

   std::map<char, int> ids = { { 'U', 0 }, { 'L', 1 }, { 'D', 2 }, { 'R', 3 } };
   std::vector<int> folding(4, 1);
   for (char s : order)
   {
      folding[(ids[s] + 2) % folding.size()] += folding[ids[s]];
      folding[(ids[s] + 1) % folding.size()] *= 2;
      folding[(ids[s] + 3) % folding.size()] *= 2;
      folding[ids[s]] = 1;
   }

   std::cout << folding[ids[side[0]]] << std::endl;
}