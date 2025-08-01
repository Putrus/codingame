#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Recipe
{
   int id;
   std::vector<int> cost;
   int price;
};

struct Spell
{
   int id;
   std::vector<int> delta;
   bool castable;

   bool areThereEnoughIngredients(const std::vector<int>& ingredients)
   {
      if (ingredients.size() != delta.size())
      {
         std::cerr << "ingredients.size() != delta.size()" << std::endl;
         return false;
      }

      for (int i = 0; i < ingredients.size(); ++i)
      {
         if (ingredients[i] + delta[i] < 0)
         {
            return false;
         }
      }

      return true;
   }
};

int main()
{
   // game loop
   while (1)
   {
      Recipe wanted_recipe = { 0 };
      std::vector<Spell> spells;
      int action_count; // the number of spells and recipes in play
      std::cin >> action_count; std::cin.ignore();
      for (int i = 0; i < action_count; i++)
      {
         int action_id; // the unique ID of this spell or recipe
         std::string action_type; // in the first league: BREW; later: CAST, OPPONENT_CAST, LEARN, BREW
         int delta_0; // tier-0 ingredient change
         int delta_1; // tier-1 ingredient change
         int delta_2; // tier-2 ingredient change
         int delta_3; // tier-3 ingredient change
         int price; // the price in rupees if this is a potion
         int tome_index; // in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax; For brews, this is the value of the current urgency bonus
         int tax_count; // in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell; For brews, this is how many times you can still gain an urgency bonus
         bool castable; // in the first league: always 0; later: 1 if this is a castable player spell
         bool repeatable; // for the first two leagues: always 0; later: 1 if this is a repeatable player spell
         std::cin >> action_id >> action_type >> delta_0 >> delta_1 >> delta_2 >> delta_3 >> price >> tome_index >> tax_count >> castable >> repeatable; std::cin.ignore();
         if (action_type == "BREW")
         {
            Recipe recipe = { action_id, { -delta_0, -delta_1, -delta_2, -delta_3 }, price };
            if (wanted_recipe.price < recipe.price)
            {
               wanted_recipe = recipe;
            }
         }
         else if (action_type == "CAST")
         {
            Spell spell = { action_id, { delta_0, delta_1, delta_2, delta_3 }, castable };
            spells.push_back(spell);
         }
      }

      std::vector<int> ingredients;
      for (int i = 0; i < 2; i++)
      {
         int inv_0; // tier-0 ingredients in inventory
         int inv_1;
         int inv_2;
         int inv_3;
         int score; // amount of rupees
         std::cin >> inv_0 >> inv_1 >> inv_2 >> inv_3 >> score; std::cin.ignore();
         if (i == 0)
         {
            ingredients = { inv_0, inv_1, inv_2, inv_3 };
         }
      }

      if (wanted_recipe.cost[0] <= ingredients[0] && wanted_recipe.cost[1] <= ingredients[1] &&
         wanted_recipe.cost[2] <= ingredients[2] && wanted_recipe.cost[3] <= ingredients[3])
      {
         std::cout << "BREW " << wanted_recipe.id << std::endl;
      }
      else
      {
         bool rest = true;
         bool end_loop = false;
         for (int i = wanted_recipe.cost.size() - 1; i >= 0; --i)
         {
            if (end_loop)
            {
               break;
            }
            if (wanted_recipe.cost[i] > ingredients[i])
            {
               for (int j = i; j >= 0; --j)
               {
                  if (spells[j].areThereEnoughIngredients(ingredients))
                  {
                     if (spells[j].castable)
                     {
                        std::cout << "CAST " << spells[j].id << std::endl;
                        rest = false;
                     }
                     end_loop = true;
                     break;
                  }
               }
            }
         }

         if (rest)
         {
            std::cout << "REST" << std::endl;
         }
      }
   }
}