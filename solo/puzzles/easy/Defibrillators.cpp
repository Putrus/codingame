#include <iostream>
#include <sstream>
#include <string>

struct Defibrillator
{
   std::string name;
   float lon;
   float lan;
};

int main()
{
   std::string lon;
   std::cin >> lon; std::cin.ignore();
   std::string lat;
   std::cin >> lat; std::cin.ignore();
   int n;
   std::cin >> n; std::cin.ignore();
   for (int i = 0; i < n; i++) {
      std::string defib;
      std::getline(std::cin, defib);
      std::stringstream ss(defib);
      int j = 0;
      std::string attr;
   }

   std::cout << "answer" << std::endl;
}