#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
   int size;
   std::cin >> size; std::cin.ignore();
   for (int i = 0; i < size; i++)
   {
      std::string row;
      std::getline(std::cin, row);

   }
   std::string clues;
   std::getline(std::cin, clues);
   std::vector<std::string> clues_vector;
   std::stringstream ss(clues);
   while (!ss.eof())
   {
      std::string c;
      ss >> c;
      clues_vector.push_back(c);
   }

   std::cout << "grid with unused letters hidden" << std::endl;
}