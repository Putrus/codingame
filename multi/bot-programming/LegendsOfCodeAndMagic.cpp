#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Card;

struct Player
{
   int health;
   int mana;
   int deck;
   int rune;
   int draw;
   std::vector<Card> board;
   std::vector<Card> hand;
};

std::istream& operator>>(std::istream& is, Player& player)
{
   is >> player.health >> player.mana >> player.deck >> player.rune >> player.draw;
   is.ignore();
   return is;
}

struct Opponent : public Player
{
   std::vector<std::string> actions;
};

std::istream& operator>>(std::istream& is, Opponent& opponent)
{
   is >> opponent.health >> opponent.mana >> opponent.deck >> opponent.rune >> opponent.draw;
   is.ignore();

   int hand, actions;
   is >> hand >> actions;
   is.ignore();
   opponent.hand = std::vector<Card>(hand);
   for (int i = 0; i < actions; ++i)
   {
      std::string card_number_and_action;
      std::getline(std::cin, card_number_and_action);
      opponent.actions.push_back(card_number_and_action);
   }
   return is;
}

struct Card
{
   int number;
   int id;
   int location;
   int type;
   int cost;
   int attack;
   int defense;
   std::string abilities;
   int player_health_change;
   int opponent_health_change;
   int draw;
};

std::istream& operator>>(std::istream& is, Card& card)
{
   is >> card.number >> card.id >> card.location >> card.type >> card.cost >> card.attack >>
      card.defense >> card.abilities >> card.player_health_change >> card.opponent_health_change >> card.draw;
   is.ignore();
   return is;
}

int main()
{
   int turn = 0;
   while (1)
   {
      Player player;
      Opponent opponent;
      std::cin >> player;
      std::cin >> opponent;
      
      int card_count;
      std::cin >> card_count; std::cin.ignore();
      for (int i = 0; i < card_count; i++)
      {
         Card card;
         std::cin >> card;
         if (card.location == 0)
         {
            player.hand.push_back(card);
         }
         else if (card.location == 1)
         {
            player.board.push_back(card);
         }
         else
         {
            opponent.board.push_back(card);
         }
      }

      //draft phase
      if (turn < 30)
      {
         int pick = std::rand() % 3;
         for (size_t i = 0; i < player.hand.size(); ++i)
         {
            if (player.hand[i].abilities.find('G') != std::string::npos)
            {
               pick = i;
               break;
            }
         }

         std::cout << "PICK " << pick << std::endl;
      }
      else
      {
         //summon
         for (const Card& card : player.hand)
         {
            if (card.cost <= player.mana)
            {
               if (card.type == 0)
               {
                  player.mana -= card.cost;
                  std::cout << "SUMMON " << card.id << ";";
                  if (card.abilities.find('C') != std::string::npos)
                  {
                     player.board.push_back(card);
                  }
               }
               else if (card.type == 1)
               {
                  if (player.board.empty())
                  {
                     continue;
                  }
                  player.mana -= card.cost;
                  std::cout << "USE " << card.id << " " << player.board[0].id << ";";
               }
               else if (card.type == 2)
               {
                  if (opponent.board.empty())
                  {
                     continue;
                  }
                  player.mana -= card.cost;
                  std::cout << "USE " << card.id << " " << opponent.board[0].id << ";";
               }
               else
               {
                  player.mana -= card.cost;
                  std::cout << "USE " << card.id << " -1;";
               }
            }
         }

         //attack
         for (const Card& card : player.board)
         {
            int target = -1;
            for (auto it = opponent.board.begin(); it != opponent.board.end();)
            {
               if (it->abilities.find('G') != std::string::npos)
               {
                  std::cout << "ATTACK " << card.id << " " << it->id << ";"; 
                  it->defense -= card.attack;
                  target = it->id;
                  if (it->defense < 0)
                  {
                     it = opponent.board.erase(it);
                  }
                  break;
               }
               else
               {
                  ++it;
               }
            }

            if (target == -1)
            {
               std::cout << "ATTACK " << card.id << " " << target << ";"; 
            }
         }

         std::cout << std::endl;
      }
      ++turn;
   }
}