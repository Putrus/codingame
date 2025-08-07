#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
std::string runBrainfuck(const std::string& code, int memory_size)
{
   std::vector<char> memory(memory_size, ' ');
   int pointer_position = 0;
   std::string output = "";
   for (int i = 0; i < code.size(); ++i)
   {
      if (code[i] == '>')
      {
         ++pointer_position;
      }
      else if (code[i] == '<')
      {
         --pointer_position;
      }
      else if (code[i] == '+')
      {
         if (memory[pointer_position] == 'Z')
         {
            memory[pointer_position] = ' ';
         }
         else if (memory[pointer_position] == ' ')
         {
            memory[pointer_position] = 'A';
         }
         else
         {
            ++memory[pointer_position];
         }
      }
      else if (code[i] == '-')
      {
         if (memory[pointer_position] == 'A')
         {
            memory[pointer_position] = ' ';
         }
         else if (memory[pointer_position] == ' ')
         {
            memory[pointer_position] = 'Z';
         }
         else
         {
            --memory[pointer_position];
         }
      }
      else if (code[i] == '.')
      {
         output += (char)(memory[pointer_position]);
      }
      else if (code[i] == '[')
      {
         int left = 1;
         int right = 0;
         int new_i = 0;
         for (int j = i + 1; j < code.size(); ++j)
         {
            if (code[j] == '[')
            {
               ++left;
            }
            else if (code[j] == ']')
            {
               ++right;
            }
            if (right == left)
            {
               new_i = j;
               break;
            }
         }

         if (right != left)
         {
            return "SYNTAX ERROR";
         }

         if (memory[pointer_position] != 0)
         {
            continue;
         }

         i = new_i;
      }
      else if (code[i] == ']')
      {
         int left = 0;
         int right = 1;
         int new_i = 0;
         for (int j = i - 1; j >= 0; --j)
         {
            if (code[j] == '[')
            {
               ++left;
            }
            else if (code[j] == ']')
            {
               ++right;
            }
            if (right == left)
            {
               new_i = j;
               break;
            }
         }

         if (right != left)
         {
            return "SYNTAX ERROR";
         }

         if (memory[pointer_position] == 0)
         {
            continue;
         }

         i = new_i;
      }
      else
      {
         return "SYNTAX ERROR";
      }

      if (pointer_position < 0 || pointer_position >= memory.size())
      {
         return "POINTER OUT OF BOUNDS";
      }

      if (memory[pointer_position] < 0 || memory[pointer_position] > 255)
      {
         return "INCORRECT VALUE";
      }
   }

   if (pointer_position < 0 || pointer_position >= memory.size())
   {
      return "POINTER OUT OF BOUNDS";
   }

   return output;
}

struct Individual
{
   std::string code;
   int fitness;

   Individual(const std::string& c, int f) : code(c), fitness(f) {}
};

int calculateFitness(const std::string& code, const std::string& phrase)
{
   std::string output = runBrainfuck(code, phrase.size());
   if (output == "SYNTAX ERROR" || output == "INCORRECT VALUE" || output == "POINTER OUT OF BOUNDS")
   {
      return std::numeric_limits<int>::max() - 1;
   }

   int fitness = 0;
   for (int i = 0; i < std::min(output.size(), phrase.size()); ++i)
   {
      if (output[i] != phrase[i])
      {
         fitness += 10;
      }
   }

   fitness += 20 * std::abs((int)phrase.size() - (int)output.size());
   fitness += code.size() / 10;

   return fitness;
}

char randomBrainfuckChar()
{
   char c = '+';
   switch (rand() % 5)
   {
   case 0: c = '>'; break;
   case 1: c = '<'; break;
   case 2: c = '+'; break;
   case 3: c = '-'; break;
   case 4: c = '.'; break;
   case 5: c = ']'; break;
   case 6: c = '['; break;
   }
   return c;
}

std::vector<Individual> createStartPopulation(int size, const std::string& phrase)
{
   std::string greedy_solution;
   for (int i = 0; i < phrase.size(); ++i)
   {
      char s = '@';
      for (int j = 0; j < phrase[i] - '@'; ++j)
      {
         greedy_solution += "+";
      }
      greedy_solution += ".";
      if (i != phrase.size() - 1)
      {
         greedy_solution += ">";
      }
   }
   Individual greedy_individual(greedy_solution, calculateFitness(greedy_solution, phrase));
   std::vector<Individual> population;
   population.push_back(greedy_individual);
   for (int i = 1; i < size; ++i)
   {
      int random_individual_length = rand() % phrase.size() * 10 + 1;
      std::string individual;
      for (int j = 0; j < random_individual_length; ++j)
      {
         individual += randomBrainfuckChar();
      }
      population.push_back(Individual(individual, calculateFitness(individual, phrase)));
   }
   return population;
}

Individual crossover(const Individual& parent1, const Individual& parent2)
{
   int cross_point = rand() % std::min(parent1.code.size(), parent2.code.size());
   std::string child_code = parent1.code.substr(0, cross_point) + parent2.code.substr(cross_point);
   return Individual(child_code, 0);
}

void mutate(Individual& individual)
{
   int mutation_point = rand() % individual.code.size();

   individual.code[mutation_point] = randomBrainfuckChar();
   int add_chance = std::rand() % 100;
   if (add_chance < 20)
   {
      individual.code.push_back(randomBrainfuckChar());
   }
   int remove_chance = std::rand() % 100;
   if (remove_chance < 10)
   {
      if (individual.code.size() < 2)
      {
         return;
      }
      individual.code.erase(individual.code.begin() + std::rand() % individual.code.size());
   }
}

int main()
{
   srand(time(nullptr));
   std::string magic_phrase;
   std::getline(std::cin, magic_phrase);

   int population_size = 1000;
   std::vector<Individual> population = createStartPopulation(population_size, magic_phrase);
   std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b)
      {
         return a.fitness < b.fitness;
      });

   std::string result = "";
   auto start_time = std::chrono::high_resolution_clock::now();
   for (int generation = 0; generation < magic_phrase.size() * 10; ++generation)
   {
      result = population[0].code;
      auto end_time = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
      if (duration.count() > 1.8)
      {
         break;
      }
      //std::cerr << result << " " << runBrainfuck(result, magic_phrase.size()) << std::endl;
      Individual first_best_individual = population[0];
      Individual second_best_individual = population[1];
      int elites = 1;
      for (int i = elites; i < population_size; ++i)
      {
         Individual child = crossover(first_best_individual, second_best_individual);
         int mutation_chance = std::rand() % 100;
         if (mutation_chance < 60)
         {
            mutate(child);
         }
         child.fitness = calculateFitness(child.code, magic_phrase);
         population[i] = child;
      }
      std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b)
         {
            return a.fitness < b.fitness;
         });
   }


   std::cout << result << std::endl;
}