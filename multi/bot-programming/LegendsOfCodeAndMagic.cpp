#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
constexpr unsigned int DRAFT_PHASE      = 0;
constexpr unsigned int BATTLE_PHASE    = 30;
constexpr char PLAYER_HAND             = 0;
constexpr char PLAYER_BOARD            = 1;
constexpr char OPPONENT_BOARD          = -1;
constexpr char OPPONENT                = -1;
enum class CardAbility : size_t
{
   Breakthrough = 0,
   Charge,
   Drain,
   Guard,
   Lethal,
   Ward,
   Length
};
enum class CardType
{
   Creature = 0,
   GreenItem,
   RedItem,
   BlueItem
};
class Card
{
public:
   double attackProfit(const Card& attacked_card) const;
   bool hasAbility(CardAbility ability) const;
   bool hasAbility(char ability) const;
   void addAttack(int attack);
   void addDefense(int defense);
   void subtractAttack(int attack);
   void subtractDefense(int defense);
   void subtractAbility(CardAbility ability);
   void subtractAbilities(std::string abilities);
   
   //getters
   int getId() const;
   int getLocation() const;
   CardType getType() const;
   int getCost() const;
   int getAttack() const;
   int getDefense() const;
   std::string getAbilities() const;
   int getPlayerHealthChange() const;
   int getOpponentHealthChange() const;
   int getDraw() const;
   bool getCanAttack() const;
   //setters
   void setDefense(int defense);
   void setCanAttack(bool can_attack);
private:
   friend std::istream& operator>>(std::istream& is, Card& card);
   friend Card operator-(Card& card, int attack);
   friend Card& operator-=(Card& card, int attack);
   friend Card operator+(Card& card, std::pair<int, int> bonus);
   friend Card& operator+=(Card& card, std::pair<int, int> bonus);
   friend Card& operator+=(Card& card, std::string abilities);
private:
   int m_number;
   int m_id;
   int m_location;
   CardType m_type;
   int m_cost;
   int m_attack;
   int m_defense;
   std::string m_abilities;
   int m_player_health_change;
   int m_opponent_health_change;
   int m_draw;
   bool m_can_attack = true;
};
double Card::attackProfit(const Card& attacked_card) const
{
   double player_value = attacked_card.m_attack >= m_defense ? m_defense + m_attack : attacked_card.m_attack;
   double opponent_value = m_attack >= attacked_card.m_defense ? attacked_card.m_defense + attacked_card.m_attack : m_attack;
   return opponent_value / player_value;
}
bool Card::hasAbility(CardAbility ability) const
{
   if (m_abilities.length() != static_cast<size_t>(CardAbility::Length))
   {
      return false;
   }
   return m_abilities.at(static_cast<size_t>(ability)) != '-';
}
bool Card::hasAbility(char ability) const
{
   if (ability == '-')
   {
      return false;
   }
   return m_abilities.find(ability) != std::string::npos;
}
void Card::addAttack(int attack)
{
   m_attack += attack;
}
void Card::addDefense(int defense)
{
   m_defense += defense;
}
void Card::subtractAttack(int attack)
{
   m_attack -= attack;
}
void Card::subtractDefense(int defense)
{
   m_defense -= defense;
}
void Card::subtractAbility(CardAbility ability)
{
   if (m_abilities.length() == static_cast<size_t>(CardAbility::Length))
   {
      m_abilities.at(static_cast<size_t>(ability)) = '-';
   }
}
void Card::subtractAbilities(std::string abilities)
{
   if (m_abilities.length() == abilities.length())
   {
      for (size_t i = 0; i < m_abilities.length(); ++i)
      {
         if (abilities[i] != '-')
         {
            m_abilities[i] = '-';
         }
      }
   }
}
int Card::getId() const
{
   return m_id;
}
int Card::getLocation() const
{
   return m_location;
}
CardType Card::getType() const
{
   return m_type;
}
int Card::getCost() const
{
   return m_cost;
}
int Card::getAttack() const
{
   return m_attack;
}
int Card::getDefense() const
{
   return m_defense;
}
std::string Card::getAbilities() const
{
   return m_abilities;
}
int Card::getPlayerHealthChange() const
{
   return m_player_health_change;
}
int Card::getOpponentHealthChange() const
{
   return m_opponent_health_change;
}
int Card::getDraw() const
{
   return m_draw;
}
bool Card::getCanAttack() const
{
   return m_can_attack;
}
void Card::setDefense(int defense)
{
   m_defense = defense;
}
void Card::setCanAttack(bool can_attack)
{
   m_can_attack = can_attack;
}
std::istream& operator>>(std::istream& is, Card& card)
{
   int type;
   is >> card.m_number >> card.m_id >> card.m_location >> type >> card.m_cost >> card.m_attack >>
      card.m_defense >> card.m_abilities >> card.m_player_health_change >> card.m_opponent_health_change >> card.m_draw;
   card.m_type = static_cast<CardType>(type);
   return is;
}
Card operator-(Card& card, int attack)
{
   Card created_card = card;
   created_card.subtractDefense(attack);
   return created_card;
}
Card& operator-=(Card& card, int attack)
{
   card.m_defense -= attack;
   return card;
}
Card operator+(Card& card, std::pair<int, int> bonus)
{
   Card created_card = card;
   created_card += bonus;
   return created_card;
}
Card& operator+=(Card& card, std::pair<int, int> bonus)
{
   card.addAttack(bonus.first);
   card.addDefense(bonus.second);
   return card;
}
Card& operator+=(Card& card, std::string abilities)
{
   if (card.m_abilities.length() == abilities.length())
   {
      for (size_t i = 0; i < abilities.length(); ++i)
      {
         if (abilities[i] != '-')
         {
            card.m_abilities[i] = abilities[i];
         }
      }
   }
   return card;
}
class BasePlayer
{
public:
   int getMana() const;
   int getHealth() const;
   void setMana(int mana);
   void setHealth(int health);
   std::vector<Card> getCards() const;
   void addCard(const Card& card);
   void clearCards();
protected:
   int m_health;
   int m_mana;
   int m_deck;
   int m_rune;
   int m_draw;
   std::vector<Card> m_cards;
};
int BasePlayer::getMana() const
{
   return m_mana;
}
int BasePlayer::getHealth() const
{
    return m_health;
}
void BasePlayer::setMana(int mana)
{
   m_mana = mana;
}
void BasePlayer::setHealth(int health)
{
   m_health = health;
}
std::vector<Card> BasePlayer::getCards() const
{
   return m_cards;
}
void BasePlayer::addCard(const Card& card)
{
   m_cards.push_back(card);
}
void BasePlayer::clearCards()
{
   m_cards.clear();
   m_cards.shrink_to_fit();
}
class Player final : public BasePlayer
{
public:
   std::vector<Card> getCards() const;
   std::vector<Card> getCards(char location) const;
   void clearCards();
   
private:
   friend std::istream& operator>>(std::istream& is, Player& player);
};
std::istream& operator>>(std::istream& is, Player& player)
{
   is >> player.m_health >> player.m_mana >> player.m_deck >> player.m_rune >> player.m_draw;
   return is;
}
std::vector<Card> Player::getCards(char location) const
{
   if (location == PLAYER_BOARD || location == PLAYER_HAND)
   {
      std::vector<Card> result = m_cards;
      result.erase(std::remove_if(result.begin(), result.end(),
         [location](auto& card)
         {
            return card.getLocation() != location;
         }), result.end());
      return result;
   }
   else
   {
      return std::vector<Card>();
   }
}
std::vector<Card> Player::getCards() const
{
   return m_cards;
}
void Player::clearCards()
{
   m_cards.clear();
   m_cards.shrink_to_fit();
}
class Opponent final : public BasePlayer
{
public:
   void clearCards();
private:
   friend std::istream& operator>>(std::istream& is, Opponent& opponent);
private:
   int m_hand;
   std::vector<std::string> m_actions;
};
std::istream& operator>>(std::istream& is, Opponent& opponent)
{
   int actions_number;
   is >> opponent.m_health >> opponent.m_mana >> opponent.m_deck >> opponent.m_rune >> opponent.m_draw >> opponent.m_hand >> actions_number;
   is.ignore();
   for (int i = 0; i < actions_number; ++i)
   {
      std::string card_number_and_action;
      std::getline(is, card_number_and_action);
      opponent.m_actions.push_back(card_number_and_action);
   }
   return is;
}
void Opponent::clearCards()
{
   m_cards.clear();
   m_cards.shrink_to_fit();
}
class Dominator
{
public:
   void makeMove(unsigned int turn, Player& player, Opponent& opponent);
private:
   void draft(Player& player, Opponent& opponent);
   void battle(Player& player, Opponent& opponent);
   double getDraftCardRatio(const Card& card);
private:
   std::vector<int> m_draft_costs_cards = { 0, 0, 0, 0, 0, 0, 0, 0 };
};
void Dominator::makeMove(unsigned int turn, Player& player, Opponent& opponent)
{
   if (turn >= DRAFT_PHASE && turn <= BATTLE_PHASE)
   {
      draft(player, opponent);
   }
   else
   {
      battle(player, opponent);
   }
}
void Dominator::draft(Player& player, Opponent& opponent)
{
   const std::vector<Card>& cards_to_choose = player.getCards();
   auto best_card = std::max_element(cards_to_choose.begin(), cards_to_choose.end(),
      [this](auto& l_card, auto& r_card)
      {
         return getDraftCardRatio(l_card) < getDraftCardRatio(r_card);
      });
   std::cout << "PICK " << std::distance(cards_to_choose.begin(), best_card) << std::endl;
}
void Dominator::battle(Player& player, Opponent& opponent)
{
   std::vector<Card> player_board_cards = player.getCards(PLAYER_BOARD);
   std::vector<Card> player_hand_cards = player.getCards(PLAYER_HAND);
   std::vector<Card> opponent_cards = opponent.getCards();
   std::sort(player_hand_cards.begin(), player_hand_cards.end(),
      [](const auto& l_card, const auto& r_card)
      {
         return l_card.getCost() > r_card.getCost();
      });
   //summon
   for (auto& player_card : player_hand_cards)
   {
      if (player.getMana() >= player_card.getCost())
      {
         switch (player_card.getType())
         {
         case CardType::Creature:
         {
            if (player_board_cards.size() < 6 && player.getHealth() > -player_card.getPlayerHealthChange())
            {
               std::cout << "SUMMON " << player_card.getId() << ';';
               if (!player_card.hasAbility(CardAbility::Charge))
               {
                  player_card.setCanAttack(false);
               }
               player_board_cards.push_back(player_card);
               player.setHealth(player.getHealth() + player_card.getPlayerHealthChange());
               player.setMana(player.getMana() - player_card.getCost());
            }
            break;
         }
         case CardType::GreenItem:
         {
            if (!player_board_cards.empty())
            {
               auto best_player_card = std::max_element(player_board_cards.begin(), player_board_cards.end(),
                  [](const auto& l_card, const auto& r_card)
                  {
                     return l_card.getAttack() + l_card.getDefense() < r_card.getAttack() + l_card.getAttack();
                  });
               *best_player_card += std::make_pair<int, int>(player_card.getAttack(), player_card.getDefense());
               *best_player_card += player_card.getAbilities();
               std::cout << "USE " << player_card.getId() << ' ' << best_player_card->getId() << ';';
               player.setMana(player.getMana() - player_card.getCost());
            }
            break;
         }
         case CardType::RedItem:
         {
            if (!opponent_cards.empty())
            {
               std::string red_card_abilities = player_card.getAbilities();
               std::cerr << "RED CARD ABILITIES: " << red_card_abilities << std::endl;
               auto best_opponent_card = std::find_if(opponent_cards.begin(), opponent_cards.end(),
                  [red_card_abilities](const auto& opponent_card)
                  {
                     for (const auto& ability : red_card_abilities)
                     {
                        if(opponent_card.hasAbility(ability))
                        {
                           return true;
                        }
                     }
                     return false;
                  });
               if (best_opponent_card != opponent_cards.end())
               {
                  std::cout << "USE " << player_card.getId() << ' ' << best_opponent_card->getId() << ';';
                  best_opponent_card->addAttack(player_card.getAttack());
                  best_opponent_card->addDefense(player_card.getDefense());
                  best_opponent_card->subtractAbilities(player_card.getAbilities());
                  if (best_opponent_card->getDefense() <= 0)
                  {
                     opponent_cards.erase(best_opponent_card);
                  }
                  player.setMana(player.getMana() - player_card.getCost());
               }
            }
            break;
         }
         case CardType::BlueItem:
         {
            std::cout << "USE " << player_card.getId() << " -1;";
            break;
         }
         }
      }
   }
   std::sort(player_board_cards.begin(), player_board_cards.end(),
      [](const auto& l_card, const auto& r_card)
      {
         return l_card.hasAbility(CardAbility::Lethal);
      });
   //attack
   for (auto& player_card : player_board_cards)
   {
      if (player_card.getAttack() == 0 || !player_card.getCanAttack())
      {
         continue;
      }
      auto guard_card = std::find_if(opponent_cards.begin(), opponent_cards.end(),
         [](const auto& card)
         {
            return card.hasAbility(CardAbility::Guard);
         });
      auto attacked_card = std::max_element(opponent_cards.begin(), opponent_cards.end(),
         [player_card](const auto& card1, const auto& card2) {
            return player_card.attackProfit(card1) < player_card.attackProfit(card2) || card2.hasAbility(CardAbility::Guard);
         });
      if (!opponent_cards.empty() && (player_card.attackProfit(*attacked_card) > 1.0 ||
         player_card.hasAbility(CardAbility::Lethal) || attacked_card->hasAbility(CardAbility::Guard)))
      {
         if (guard_card == opponent_cards.end() && opponent.getHealth() < player_card.getAttack())
         {
            std::cout << "ATTACK " << player_card.getId() << " " << static_cast<int>(OPPONENT) << ';';
         }
         std::cout << "ATTACK " << player_card.getId() << " " << attacked_card->getId() << ';';
         if (attacked_card->hasAbility(CardAbility::Ward))
         {
            attacked_card->subtractAbility(CardAbility::Ward);
         }
         else
         {
            attacked_card->setDefense(attacked_card->getDefense() - player_card.getAttack());
            if (attacked_card->getDefense() <= 0 || player_card.hasAbility(CardAbility::Lethal))
            {
               opponent_cards.erase(attacked_card);
            }
         }
      }
      else
      {
         std::cout << "ATTACK " << player_card.getId() << " " << static_cast<int>(OPPONENT) << ';';
      }
   }
   std::cout << "PASS" << std::endl;
}
double Dominator::getDraftCardRatio(const Card& card)
{
   int breakthrough_bonus = card.hasAbility(CardAbility::Breakthrough) ? card.getAttack() + 1 : 0;
   int charge_bonus = card.hasAbility(CardAbility::Charge) ? card.getAttack() + 1: 0;
   int drain_bonus = card.hasAbility(CardAbility::Drain) ? card.getAttack() + 1: 0;
   int guard_bonus = card.hasAbility(CardAbility::Guard) ? card.getAttack() + card.getDefense() + 1 : 0;
   int lethal_bonus = card.hasAbility(CardAbility::Lethal) ? card.getAttack() + card.getDefense() + 1 : 0;
   int ward_bonus = card.hasAbility(CardAbility::Ward) ? card.getAttack() + 1: 0;
   int abilities_bonus = breakthrough_bonus + charge_bonus + drain_bonus + guard_bonus + lethal_bonus + ward_bonus;
   return (card.getAttack() + card.getDefense() + abilities_bonus + card.getPlayerHealthChange() - card.getOpponentHealthChange())
      / (static_cast<double>(card.getCost()) + 0.5);
}
class Game
{
public:
   void start();
private:
   void updateTurn();
   void updatePlayers();
   void updateCards();
private:
   unsigned int m_turn = DRAFT_PHASE;
   Player m_player;
   Opponent m_opponent;
   Dominator m_dominator;
};
void Game::start()
{
   //game loop
   while (true) 
   {
      updateTurn();
      updatePlayers();
      updateCards();
      m_dominator.makeMove(m_turn, m_player, m_opponent);
      m_player.clearCards();
      m_opponent.clearCards();
   }
}
void Game::updateTurn()
{
   ++m_turn;
}
void Game::updatePlayers()
{
   std::cin >> m_player >> m_opponent;
}
void Game::updateCards()
{
   int card_count;
   std::cin >> card_count; 
   std::cin.ignore();
   for (int i = 0; i < card_count; ++i) 
   {
      Card card;
      std::cin >> card;
      if (card.getLocation() == OPPONENT_BOARD)
      {
         m_opponent.addCard(card);
      }
      else
      {
         m_player.addCard(card);
      }
   }
}
int main()
{
   Game game;
   game.start();
   return 0;
}