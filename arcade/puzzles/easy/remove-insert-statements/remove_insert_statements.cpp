#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> split(std::string s, std::string delimiter)
{
   size_t pos_start = 0;
   size_t pos_end = 0;
   size_t delimiter_length = delimiter.length();
   std::string token;
   std::vector<std::string> result;

   while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
   {
      result.push_back(s.substr(pos_start, (pos_end - pos_start) + delimiter_length));
      pos_start = pos_end + delimiter_length;
   }

   if (pos_start < s.size())
      result.push_back(s.substr(pos_start));

   return result;
}

std::string toLower(const std::string& str)
{
   std::string lower_str = str;
   std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
      [](unsigned char c){ return std::tolower(c); });
   return lower_str;
}

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   bool begin = false;
   bool insert = false;
   for (int i = 0; i < n; i++)
   {
      std::string fname;
      std::getline(std::cin, fname);
      std::string lower_fname = toLower(fname);
      if (begin)
      {
         std::cout << fname << std::endl;
         if (lower_fname.substr(0, 4) == "end;")
         {
            begin = false;
         }
         continue;
      }

      if (insert)
      {
         if (lower_fname.find(";") != std::string::npos)
         {
            insert = false;
         }
         continue;
      }
      
      if (lower_fname.substr(0, 5) == "begin")
      {
         begin = true;
         std::cout << fname << std::endl;
         continue;
      }

      if (lower_fname.substr(0, 6) == "insert" && lower_fname.find(";") == std::string::npos)
      {
         insert = true;
         continue;
      }

      std::vector<std::string> parts = split(fname, ";");
      
      bool empty = true;
      for (const std::string& part : parts)
      {
         std::string lower = toLower(part);
         if (lower.substr(0, 6) == "insert")
         {
            continue;
         }
         else
         {
            empty = false;
            std::cout << part;
         }
      }
      if (i != n - 1 && !empty)
      {
         std::cout << std::endl;
      }
   }
}