#include <iostream>
#include <map>
#include <string>

int main()
{
   std::map<std::string, std::string> mime;
   int n; // Number of elements which make up the association table.
   std::cin >> n; std::cin.ignore();
   int q; // Number Q of file names to be analyzed.
   std::cin >> q; std::cin.ignore();
   for (int i = 0; i < n; i++)
   {
      std::string ext; // file extension
      std::string mt; // MIME type.
      std::cin >> ext >> mt; std::cin.ignore();
      for (char& c : ext)
      {
         c = std::tolower(c);
      }
      
      if (mime.find(ext) == mime.end())
      {
         mime.insert({ ext, mt });
      }
   }
   for (int i = 0; i < q; i++)
   {
      std::string fname;
      std::getline(std::cin, fname); // One file name per line.
      size_t dot_position = fname.find_last_of('.');
      if (dot_position == std::string::npos)
      {
         std::cout << "UNKNOWN" << std::endl;
         continue;
      }

      std::string ext = fname.substr(dot_position + 1);
      for (char& c : ext)
      {
         c = std::tolower(c);
      }
      if (mime.find(ext) != mime.end())
      {
         std::cout << mime[ext] << std::endl;
      }
      else
      {
         std::cout << "UNKNOWN" << std::endl;
      }
   }
}