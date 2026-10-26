#include <iostream>
#include <string>
#include <vector>

constexpr int ZONES_SIZE = 30;
constexpr int ALPHABET_SIZE = 27; // 26 letters + space

class Utility
{
public:
   static int shortestDelta(char from, char to)
   {
      int from_val = (from == ' ') ? 0 : from - 'A' + 1;
      int to_val = (to == ' ') ? 0 : to - 'A' + 1;

      int delta = (to_val - from_val + ALPHABET_SIZE) % ALPHABET_SIZE;
      if (delta > ALPHABET_SIZE / 2)
      {
         delta -= ALPHABET_SIZE;
      }
      return delta;
   }

   static int shortestDistance(int from, int to)
   {
      int distance = (to - from + ZONES_SIZE) % ZONES_SIZE;
      if (distance > ZONES_SIZE / 2)
      {
         distance -= ZONES_SIZE;
      }
      return distance;
   }
};

class Zone
{
public:
   Zone& operator++(int value)
   {
      if (rune == ' ')
      {
         rune = 'A';
      }
      else if (rune == 'Z')
      {
         rune = ' ';
      }
      else
      {
         ++rune;
      }
      return *this;
   }

   Zone& operator--(int value)
   {
      if (rune == ' ')
      {
         rune = 'Z';
      }
      else if (rune == 'A')
      {
         rune = ' ';
      }
      else
      {
         --rune;
      }
      return *this;
   }

   int shortestDelta(char rune) const
   {
      return Utility::shortestDelta(this->rune, rune);
   }

   char getRune() const
   {
      return rune;
   }

private:
   char rune = ' ';
};

class Forest
{
public:
   Forest(int zones_size) : zones(std::vector<Zone>(zones_size, Zone())) {}
   std::vector<Zone> zones;
};

class Blub
{
public:
   Blub(Forest& forest) : forest(forest) {}

   void applyInstruction(char instruction)
   {
      if (instruction == '>')
      {
         ++position;
         if (position >= ZONES_SIZE)
         {
            position = 0;
         }
      }
      else if (instruction == '<')
      {
         --position;
         if (position < 0)
         {
            position = ZONES_SIZE - 1;
         }
      }
      else if (instruction == '+')
      {
         forest.zones[position]++;
      }
      else if (instruction == '-')
      {
         forest.zones[position]--;
      }
      else if (instruction == '.')
      {
         phrase += forest.zones[position].getRune();
      }
   }

   void applyInstructions(const std::string& instructions)
   {
      for (char instruction : instructions)
      {
         applyInstruction(instruction);
      }
   }

   std::string findBestInstructions(char target_rune)
   {
      std::string best_instructions;
      for (int i = 0; i < forest.zones.size(); ++i)
      {
         std::string instructions;
         int distance = Utility::shortestDistance(position, i);
         char instruction = (distance > 0) ? '>' : '<';
         instructions += std::string(std::abs(distance), instruction);
         int delta = forest.zones[i].shortestDelta(target_rune);
         instruction = (delta > 0) ? '+' : '-';
         instructions += std::string(std::abs(delta), instruction);
         instructions += '.';
         if (instructions.size() < best_instructions.size() || best_instructions.empty())
         {
            best_instructions = instructions;
         }
      }
      return best_instructions;
   }

   std::string getPhrase() const
   {
      return phrase;
   }

private:
   Forest& forest;
   int position = 0;
   std::string phrase;
};

int main()
{
   std::string magic_phrase;
   std::getline(std::cin, magic_phrase);
   std::string instructions;
   Forest forest(ZONES_SIZE);
   Blub blub(forest);
   for (char rune : magic_phrase)
   {
      std::string best_instructions = blub.findBestInstructions(rune);
      blub.applyInstructions(best_instructions);
      instructions += best_instructions;
   }
   std::cout << instructions << std::endl;
}