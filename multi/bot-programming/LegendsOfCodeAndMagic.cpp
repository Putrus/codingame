#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Card begin
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

   enum class Location : int
   {
      PlayerHand = 0,
      PlayerBoard,
      OpponentBoard
   };

   enum class Type : int
   {
      Creature = 0,
      GreenItem,
      RedItem,
      BlueItem
   };
};

bool operator==(int number, Card::Location location)
{
   return number == static_cast<int>(location);
}

bool operator==(int number, Card::Type type)
{
   return number == static_cast<int>(type);
}

std::istream& operator>>(std::istream& is, Card& card)
{
   is >> card.number >> card.id >> card.location >> card.type >> card.cost >> card.attack >>
      card.defense >> card.abilities >> card.player_health_change >> card.opponent_health_change >> card.draw;
   is.ignore();
   return is;
}
// Card end

//Player begin
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
//Player end

//Opponent begin
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
//Opponent end

//Game begin
class Game
{
public:
   void run();

private:
   void attack();
   void battle();
   void clear();
   void draft() const;
   void input();
   void play();
   void summon();

   int turn = 0;

   Player player;
   Opponent opponent;
};

void Game::run()
{
   for (turn = 0; true; ++turn)
   {
      input();
      play();
      clear();
   }
}

void Game::attack()
{
   for (const Card& card : player.board)
   {
      int target = -1;
      for (auto it = opponent.board.begin(); it != opponent.board.end();)
      {
         if (it->abilities.find('G') != std::string::npos)
         {
            if (card.attack <= 0)
            {
               continue;
            }
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

      if (target == -1 && card.attack > 0)
      {
         std::cout << "ATTACK " << card.id << " " << target << ";"; 
      }
   }

   std::cout << std::endl;
}

void Game::battle()
{
   summon();
   attack();
}

void Game::clear()
{
   player.hand.clear();
   player.board.clear();
   opponent.board.clear();
}

void Game::draft() const
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

void Game::input()
{
   std::cin >> player;
   std::cin >> opponent;
   
   int card_count;
   std::cin >> card_count; std::cin.ignore();
   for (int i = 0; i < card_count; i++)
   {
      Card card;
      std::cin >> card;
      if (card.location == Card::Location::PlayerHand)
      {
         player.hand.push_back(card);
      }
      else if (card.location == Card::Location::PlayerBoard)
      {
         player.board.push_back(card);
      }
      else
      {
         opponent.board.push_back(card);
      }
   }
}

void Game::play()
{
   if (turn < 30)
   {
      draft();
   }
   else
   {
      battle();
   }
}

void Game::summon()
{
   std::sort(player.hand.begin(), player.hand.end(),
      [](const auto& lhs, const auto& rhs)
      {
         return lhs.cost > rhs.cost;
      });
   
   auto find_guard = std::find_if(player.hand.begin(), player.hand.end(), [this](const auto& card)
      {
         return card.type == Card::Type::Creature && card.cost <= player.mana && card.abilities.find('G') != std::string::npos;
      });

   int guard_id = -1;
   if (find_guard != player.hand.end())
   {
      guard_id = find_guard->id;
      player.mana -= find_guard->cost;
      std::cout << "SUMMON " << find_guard->id << ";";
   }

   for (const Card& card : player.hand)
   {
      if (card.id == guard_id)
      {
         continue;
      }

      if (card.cost <= player.mana)
      {
         if (card.type == Card::Type::Creature)
         {
            player.mana -= card.cost;
            std::cout << "SUMMON " << card.id << ";";
            if (card.abilities.find('C') != std::string::npos)
            {
               player.board.push_back(card);
            }
         }
         else if (card.type == Card::Type::GreenItem)
         {
            if (player.board.empty())
            {
               continue;
            }
            player.mana -= card.cost;

            auto best = std::max_element(player.board.begin(), player.board.end(), [](const auto& lhs, const auto& rhs)
               {
                  return (lhs.attack + lhs.defense) < (rhs.attack + rhs.defense);
               });
            std::cout << "USE " << card.id << " " << best->id << ";";
         }
         else if (card.type == Card::Type::RedItem)
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
}
//Game end

int main()
{
   try
   {
      Game game;
      game.run();
   }
   catch (const std::exception& e)
   {
      std::cerr << e.what() << std::endl;
   }
}