#include <iostream>
#include <string>
#include <sstream>
int main()
{
   std::string t;
   getline(std::cin, t);

   std::stringstream ss(t);
   while (!ss.eof())
   {
      std::string r;
      ss >> r;
      std::string substr = r.substr(r.size() - 2, 2);
      if (substr == "nl")
      {
         std::cout << std::endl;
      }
      else if (substr == "sp")
      {
         int n = stoi(r.substr(0, r.size() - 2));
         for (int i = 0; i < n; ++i)
         {
            std::cout << ' ';
         }
      }
      else if (substr == "bS")
      {
         int n = stoi(r.substr(0, r.size() - 2));
         for (int i = 0; i < n; ++i)
         {
            std::cout << '\\';
         }
      }
      else if (substr == "sQ")
      {
         int n = stoi(r.substr(0, r.size() - 2));
         for (int i = 0; i < n; ++i)
         {
            std::cout << '\'';
         }
      }
      else
      {
         int n = stoi(r.substr(0, r.size() - 1));
         for (int i = 0; i < n; ++i)
         {
            std::cout << r.back();
         }
      }
   }
}