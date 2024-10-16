#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

bool isCreationPossible(const std::string& word, const std::string& letters)
{
   int i = 0;
   bool possible = true;
   for (char c : word)
   {
      if (i == letters.size())
      {
         possible = false;
         break;
      }

      while (i < letters.size())
      {
         if (letters[i] == c)
         {
            ++i;
            break;
         }
         ++i;
         if (i == letters.size())
         {
            possible = false;
            break;
         }
      }
   }
   return possible;
}

int calcPoints(const std::string& word, const std::map<char, int>& points)
{
   int p = 0;
   for (char c : word)
   {
      p += points.at(c);
   }
   return p;
}

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<std::string> words;
   for (int i = 0; i < n; i++) 
   {
      std::string w;
      getline(std::cin, w);
      words.push_back(w);
   }
   std::string letters;
   getline(std::cin, letters);

   std::sort(letters.begin(), letters.end());

   std::map<char, int> points = { { 'a', 1 }, { 'b', 3 }, { 'c', 3 }, { 'd', 2 },
      { 'e', 1 }, { 'f', 4 }, { 'g', 2 }, { 'h', 4 }, { 'i', 1 }, { 'j', 8 },
      { 'k', 5 }, { 'l', 1 }, { 'm', 3 }, { 'n', 1 }, { 'o', 1 }, { 'p', 3 },
      { 'q', 10}, { 'r', 1 }, { 's', 1 }, { 't', 1 }, { 'u', 1 }, { 'v', 4 },
      { 'w', 4 }, { 'x', 8 }, { 'y', 4 }, { 'z', 10} };

   std::string best_word = "";
   int best_score = 0;
   for (const auto& word : words)
   {
      std::string copy = word;
      std::sort(copy.begin(), copy.end());

      int p = calcPoints(copy, points);
      if (isCreationPossible(copy, letters) && p > best_score)
      {
         best_score = p;
         best_word = word;
      }
   }

   std::cout << best_word << std::endl;
}