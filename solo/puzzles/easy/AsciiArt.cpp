#include <iostream>
#include <string>
#include <vector>

int main()
{
   int l;
   std::cin >> l; std::cin.ignore();
   int h;
   std::cin >> h; std::cin.ignore();
   std::string t;
   std::getline(std::cin, t);
   std::vector<std::string> ascii_art;
   std::vector<std::string> result;
   for (int i = 0; i < h; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      ascii_art.push_back(row);
      result.push_back("");
   }

   for (char c : t)
   {
      char upper_c = std::toupper(c);
      int id = upper_c - 'A';
      if (id < 0 || id > 26)
      {
         id = 26;
      }
      for (int i = 0; i < result.size(); ++i)
      {
         for (int j = id * l; j < id * l + l; ++j)
         {
            result[i] += ascii_art[i][j];
         }
      }
   }

   for (const auto& row : result)
   {
      std::cout << row << std::endl;
   }
}