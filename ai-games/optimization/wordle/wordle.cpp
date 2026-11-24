#include <iostream>
#include <string>
#include <vector>
#include <array>

constexpr int WORD_SIZE = 6;

std::string getPattern(const std::string& guess, const std::string& answer)
{
   std::string result(WORD_SIZE, '1');
   std::array<int, 26> count{};

   // green letters
   for (int i = 0; i < WORD_SIZE; ++i)
   {
      if (guess[i] == answer[i])
      {
         result[i] = '3';
      }
      else
      {
         count[answer[i] - 'A']++;
      }
   }

   // yellow letters
   for (int i = 0; i < WORD_SIZE; ++i)
   {
      if (result[i] == '3')
         continue;

      int c = guess[i] - 'A';

      if (count[c] > 0)
      {
         result[i] = '2';
         count[c]--;
      }
   }

   return result;
}

std::string chooseWord(const std::vector<std::string>& candidates)
{
   std::string best_word = candidates.front();
   int best_score = -1;

   for (const auto& candidate : candidates)
   {
      std::array<bool, 26> used{};
      int score = 0;

      for (char c : candidate)
      {
         if (!used[c - 'A'])
         {
            used[c - 'A'] = true;
            score++;
         }
      }

      if (score > best_score)
      {
         best_score = score;
         best_word = candidate;
      }
   }

   return best_word;
}

int main()
{
   int word_count;
   std::cin >> word_count;

   std::vector<std::string> candidates;
   candidates.reserve(word_count);

   for (int i = 0; i < word_count; ++i)
   {
      std::string word;
      std::cin >> word;
      candidates.push_back(word);
   }

   std::string word = "SORTED";
   bool first_try = true;

   // Game loop
   while (true)
   {
      std::string pattern(WORD_SIZE, '1');

      for (int i = 0; i < WORD_SIZE; ++i)
      {
         int state; // state of the letter of the corresponding position of previous guess
         std::cin >> state; std::cin.ignore();

         pattern[i] = '0' + state;
      }

      if (first_try)
      {
         first_try = false;
         std::cout << word << std::endl;
         continue;
      }

      // remove incorrect words
      std::vector<std::string> next_candidates;
      next_candidates.reserve(candidates.size());

      for (const auto& candidate : candidates)
      {
         if (getPattern(word, candidate) == pattern)
         {
            next_candidates.push_back(candidate);
         }
      }

      candidates = std::move(next_candidates);

      if (candidates.empty())
      {
         std::cout << word << std::endl;
         continue;
      }

      word = chooseWord(candidates);

      std::cout << word << std::endl;
   }

   return 0;
}
