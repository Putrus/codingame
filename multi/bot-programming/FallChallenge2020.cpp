#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Recipe
{
   int id;
   int cost_0;
   int cost_1;
   int cost_2;
   int cost_3;
   int price;
};

int main()
{

   // game loop
   while (1)
   {
      std::vector<Recipe> recipes;

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
         std::cerr << action_id << " " << delta_0 << std::endl;
         int price; // the price in rupees if this is a potion
         int tome_index; // in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax; For brews, this is the value of the current urgency bonus
         int tax_count; // in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell; For brews, this is how many times you can still gain an urgency bonus
         bool castable; // in the first league: always 0; later: 1 if this is a castable player spell
         bool repeatable; // for the first two leagues: always 0; later: 1 if this is a repeatable player spell
         std::cin >> action_id >> action_type >> delta_0 >> delta_1 >> delta_2 >> delta_3 >> price >> tome_index >> tax_count >> castable >> repeatable; std::cin.ignore();
         Recipe recipe = {action_id, -delta_0, -delta_1, -delta_2, -delta_3, price};
         recipes.push_back(recipe);
      }

      int recipe_id = 0;
      int price = 0;
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
            for (const auto& recipe : recipes)
            {
               if (recipe.cost_0 <= inv_0 && recipe.cost_1 <= inv_1 && recipe.cost_2 <= inv_2 && recipe.cost_3 <= inv_3 && recipe.price > price)
               {
                  recipe_id = recipe.id;
                  price = recipe.price;
               }
            }
         }
      }
      // in the first league: BREW <id> | WAIT; later: BREW <id> | CAST <id> [<times>] | LEARN <id> | REST | WAIT
      std::cout << "BREW " << recipe_id << std::endl;
   }
}