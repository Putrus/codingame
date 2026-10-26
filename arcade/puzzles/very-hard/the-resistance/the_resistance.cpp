#include <iostream>
#include <string>
#include <vector>
#include <map>

constexpr size_t M = 20;
constexpr size_t MAXIMUM_MORSE_LENGTH = 4;
constexpr std::array<std::string_view, 26> ALPHABET = {
   ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
   "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

std::string toMorse(const std::string& str)
{
   std::string morse;
   for (char c : str)
   {
      morse += ALPHABET[c - 'A'];
   }
   return morse;
}

long long solve(size_t start, const std::string& l, const std::map<std::string, long long>& words, std::map<size_t, long long>& dp)
{
   if (start == l.length())
   {
      return 1;
   }

   if (dp.find(start) != dp.end())
   {
      return dp[start];
   }

   long long count = 0;
   for (int i = 1; i <= M * MAXIMUM_MORSE_LENGTH && start + i <= l.length(); i++)
   {
      long long n = words.find(l.substr(start, i)) == words.end() ? 0 : words.at(l.substr(start, i));
      if (n > 0)
      {
         count += n * solve(start + i, l, words, dp);
      }
   }

   dp[start] = count;
   return count;
}

int main()
{
   std::string l;
   std::cin >> l; std::cin.ignore();
   int n;
   std::cin >> n; std::cin.ignore();
   std::map<std::string, long long> words;
   for (int i = 0; i < n; i++)
   {
      std::string w;
      std::cin >> w; std::cin.ignore();
      std::string morse = toMorse(w);
      if (words.find(morse) != words.end())
      {
         words[morse]++;
      }
      else
      {
         words.insert({morse, 1});
      }
   }
   std::map<size_t, long long> dp;
   long long result = solve(0, l, words, dp);

   std::cout << result << std::endl;
}