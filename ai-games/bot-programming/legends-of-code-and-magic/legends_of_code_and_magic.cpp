#include <algorithm>
#include <cmath>
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
   void takeDamage(int damage, bool is_lethal = false);
   
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
   if (m_attack <= 0)
   {
      return -100.0;
   }

   bool kills_target = false;
   if (!attacked_card.hasAbility(CardAbility::Ward))
   {
      kills_target = hasAbility(CardAbility::Lethal) || (m_attack >= attacked_card.m_defense);
   }

   bool survives = false;
   if (hasAbility(CardAbility::Ward))
   {
      survives = true;
   }
   else if (!attacked_card.hasAbility(CardAbility::Lethal) && attacked_card.m_attack < m_defense)
   {
      survives = true;
   }

   double target_value = attacked_card.m_attack + attacked_card.m_defense;
   if (attacked_card.hasAbility(CardAbility::Guard))
   {
      target_value += 3.0;
   }
   if (attacked_card.hasAbility(CardAbility::Lethal))
   {
      target_value += 3.0;
   }
   if (attacked_card.hasAbility(CardAbility::Ward))
   {
      target_value += 2.0;
   }

   double my_value = m_attack + m_defense;

   // Free trade: we kill opponent creature and survive
   if (kills_target && survives)
   {
      return 10.0 + target_value;
   }

   // Mutual kill: both creatures die
   if (kills_target && !survives)
   {
      double threat_bonus = (attacked_card.m_attack >= 4) ? 2.5 : ((attacked_card.m_attack >= 3) ? 1.0 : 0.0);
      return 2.0 + (target_value - my_value) + threat_bonus;
   }

   // Survives and damages target or pops Ward
   if (!kills_target && survives)
   {
      if (attacked_card.hasAbility(CardAbility::Ward))
      {
         return 3.0 - (m_attack * 0.2);
      }
      return 1.0 + (static_cast<double>(m_attack) - attacked_card.m_attack);
   }

   // Dies without killing target
   if (attacked_card.hasAbility(CardAbility::Ward))
   {
      return -5.0;
   }
   return -10.0 + (static_cast<double>(m_attack) - my_value);
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

void Card::takeDamage(int damage, bool is_lethal)
{
   if (damage <= 0 && !is_lethal)
   {
      return;
   }
   if (hasAbility(CardAbility::Ward))
   {
      subtractAbility(CardAbility::Ward);
      return;
   }
   if (is_lethal)
   {
      m_defense = 0;
   }
   else
   {
      m_defense -= damage;
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
   created_card.takeDamage(attack);
   return created_card;
}

Card& operator-=(Card& card, int attack)
{
   card.takeDamage(attack);
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
   double getDraftCardRatio(const Card& card) const;

private:
   std::vector<int> m_draft_costs_cards = { 0, 0, 0, 0, 0, 0, 0, 0 };
   int m_items_count = 0;
   int m_guards_count = 0;
   int m_pick_number = 0;
};

void Dominator::makeMove(unsigned int turn, Player& player, Opponent& opponent)
{
   if (turn == 1)
   {
      m_draft_costs_cards.assign(8, 0);
      m_items_count = 0;
      m_guards_count = 0;
      m_pick_number = 0;
   }

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
   if (cards_to_choose.empty())
   {
      std::cout << "PASS" << std::endl;
      return;
   }

   auto best_card = std::max_element(cards_to_choose.begin(), cards_to_choose.end(),
      [this](auto& l_card, auto& r_card)
      {
         return getDraftCardRatio(l_card) < getDraftCardRatio(r_card);
      });

   int cost_bucket = std::min(best_card->getCost(), 7);
   m_draft_costs_cards[cost_bucket]++;
   if (best_card->getType() != CardType::Creature)
   {
      ++m_items_count;
   }
   if (best_card->hasAbility(CardAbility::Guard))
   {
      ++m_guards_count;
   }
   ++m_pick_number;

   std::cout << "PICK " << std::distance(cards_to_choose.begin(), best_card) << std::endl;
}

void Dominator::battle(Player& player, Opponent& opponent)
{
   std::vector<Card> player_board_cards = player.getCards(PLAYER_BOARD);
   std::vector<Card> player_hand_cards = player.getCards(PLAYER_HAND);
   std::vector<Card> opponent_cards = opponent.getCards();

   // 1. Optimal subset selection of hand cards to spend maximum mana efficiently
   int hand_size = static_cast<int>(player_hand_cards.size());
   int best_subset_mask = 0;
   double best_subset_score = -1e9;

   for (int mask = 0; mask < (1 << hand_size); ++mask)
   {
      int cost_sum = 0;
      int creature_count = 0;
      int green_item_count = 0;
      int red_item_count = 0;

      for (int i = 0; i < hand_size; ++i)
      {
         if (mask & (1 << i))
         {
            cost_sum += player_hand_cards[i].getCost();
            if (player_hand_cards[i].getType() == CardType::Creature) ++creature_count;
            else if (player_hand_cards[i].getType() == CardType::GreenItem) ++green_item_count;
            else if (player_hand_cards[i].getType() == CardType::RedItem) ++red_item_count;
         }
      }

      if (cost_sum > player.getMana()) continue;
      if (player_board_cards.size() + creature_count > 6) continue;
      if (green_item_count > 0 && player_board_cards.empty() && creature_count == 0) continue;
      if (red_item_count > 0 && opponent_cards.empty()) continue;

      double subset_score = cost_sum * 100.0;
      for (int i = 0; i < hand_size; ++i)
      {
         if (mask & (1 << i))
         {
            const auto& card = player_hand_cards[i];
            if (card.getType() == CardType::Creature)
            {
               subset_score += card.getAttack() * 2.0 + card.getDefense() * 1.5 + card.getDraw() * 15.0;
               if (card.hasAbility(CardAbility::Charge)) subset_score += 12.0;
               if (card.hasAbility(CardAbility::Ward)) subset_score += 10.0;
               if (card.hasAbility(CardAbility::Guard)) subset_score += 8.0;
               if (card.hasAbility(CardAbility::Lethal)) subset_score += 8.0;
            }
            else if (card.getType() == CardType::GreenItem)
            {
               subset_score += card.getAttack() * 2.0 + card.getDefense() * 1.5 + card.getDraw() * 15.0;
               if (card.hasAbility(CardAbility::Charge)) subset_score += 15.0;
               if (card.hasAbility(CardAbility::Ward)) subset_score += 12.0;
            }
            else if (card.getType() == CardType::RedItem)
            {
               subset_score += std::abs(card.getDefense()) * 2.5 + std::abs(card.getAttack()) * 1.0 + card.getDraw() * 15.0;
            }
            else if (card.getType() == CardType::BlueItem)
            {
               subset_score += std::abs(card.getDefense()) * 2.0 - card.getOpponentHealthChange() * 1.5 + card.getDraw() * 15.0;
            }
         }
      }

      if (subset_score > best_subset_score)
      {
         best_subset_score = subset_score;
         best_subset_mask = mask;
      }
   }

   std::vector<Card> cards_to_play;
   for (int i = 0; i < hand_size; ++i)
   {
      if (best_subset_mask & (1 << i))
      {
         cards_to_play.push_back(player_hand_cards[i]);
      }
   }

   // Order execution: RedItems & damage BlueItems first, then Creatures, then GreenItems, then face BlueItems
   std::sort(cards_to_play.begin(), cards_to_play.end(),
      [](const Card& a, const Card& b)
      {
         auto get_order = [](const Card& c)
         {
            if (c.getType() == CardType::RedItem) return 0;
            if (c.getType() == CardType::BlueItem && c.getDefense() < 0) return 1;
            if (c.getType() == CardType::Creature) return 2;
            if (c.getType() == CardType::GreenItem) return 3;
            return 4;
         };
         return get_order(a) < get_order(b);
      });

   for (auto& player_card : cards_to_play)
   {
      if (player.getMana() < player_card.getCost())
      {
         continue;
      }

      switch (player_card.getType())
      {
      case CardType::Creature:
      {
         if (player_board_cards.size() < 6 && player.getHealth() > -player_card.getPlayerHealthChange())
         {
            std::cout << "SUMMON " << player_card.getId() << ';';
            player_card.setCanAttack(player_card.hasAbility(CardAbility::Charge));
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
                  int l_val = l_card.getAttack() + l_card.getDefense() + (l_card.getCanAttack() ? 6 : 0);
                  int r_val = r_card.getAttack() + r_card.getDefense() + (r_card.getCanAttack() ? 6 : 0);
                  return l_val < r_val;
               });
            *best_player_card += std::make_pair<int, int>(player_card.getAttack(), player_card.getDefense());
            *best_player_card += player_card.getAbilities();
            if (best_player_card->hasAbility(CardAbility::Charge))
            {
               best_player_card->setCanAttack(true);
            }
            std::cout << "USE " << player_card.getId() << ' ' << best_player_card->getId() << ';';
            player.setMana(player.getMana() - player_card.getCost());
         }
         break;
      }
      case CardType::RedItem:
      {
         if (!opponent_cards.empty())
         {
            auto best_opponent_card = opponent_cards.end();

            // Priority 1: enemy Guard creature
            for (auto it = opponent_cards.begin(); it != opponent_cards.end(); ++it)
            {
               if (it->hasAbility(CardAbility::Guard))
               {
                  best_opponent_card = it;
                  break;
               }
            }

            // Priority 2: highest attack threat
            if (best_opponent_card == opponent_cards.end())
            {
               best_opponent_card = std::max_element(opponent_cards.begin(), opponent_cards.end(),
                  [](const auto& l_card, const auto& r_card)
                  {
                     return l_card.getAttack() < r_card.getAttack();
                  });
            }

            if (best_opponent_card != opponent_cards.end())
            {
               std::cout << "USE " << player_card.getId() << ' ' << best_opponent_card->getId() << ';';
               best_opponent_card->subtractAbilities(player_card.getAbilities());
               best_opponent_card->addAttack(player_card.getAttack());
               if (player_card.getDefense() < 0)
               {
                  best_opponent_card->takeDamage(-player_card.getDefense());
               }
               else
               {
                  best_opponent_card->addDefense(player_card.getDefense());
               }
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
         auto best_target = opponent_cards.end();
         if (player_card.getDefense() < 0 && !opponent_cards.empty())
         {
            int dmg = -player_card.getDefense();
            for (auto it = opponent_cards.begin(); it != opponent_cards.end(); ++it)
            {
               if (it->hasAbility(CardAbility::Guard) && it->getDefense() <= dmg && !it->hasAbility(CardAbility::Ward))
               {
                  best_target = it;
                  break;
               }
            }
         }

         if (best_target != opponent_cards.end())
         {
            std::cout << "USE " << player_card.getId() << ' ' << best_target->getId() << ';';
            best_target->takeDamage(-player_card.getDefense());
            if (best_target->getDefense() <= 0)
            {
               opponent_cards.erase(best_target);
            }
         }
         else
         {
            std::cout << "USE " << player_card.getId() << " -1;";
         }
         player.setMana(player.getMana() - player_card.getCost());
         break;
      }
      }
   }

   // 2. Direct lethal check: if face damage can win the game right now
   bool has_guards = std::any_of(opponent_cards.begin(), opponent_cards.end(),
      [](const Card& card) { return card.hasAbility(CardAbility::Guard); });

   if (!has_guards)
   {
      int total_face_damage = 0;
      for (const auto& card : player_board_cards)
      {
         if (card.getCanAttack() && card.getAttack() > 0)
         {
            total_face_damage += card.getAttack();
         }
      }

      if (total_face_damage >= opponent.getHealth())
      {
         for (auto& card : player_board_cards)
         {
            if (card.getCanAttack() && card.getAttack() > 0)
            {
               std::cout << "ATTACK " << card.getId() << " -1;";
               card.setCanAttack(false);
            }
         }
         std::cout << "PASS" << std::endl;
         return;
      }
   }

   // 3. Combat resolution: clear Guards first with optimal trades, then face or free trades
   while (true)
   {
      // Find remaining guards
      std::vector<Card> guard_opponent_cards;
      std::copy_if(opponent_cards.begin(), opponent_cards.end(), std::back_inserter(guard_opponent_cards),
         [](const Card& card) { return card.hasAbility(CardAbility::Guard); });

      if (guard_opponent_cards.empty())
      {
         break;
      }

      // Check if any guard has Ward: pop it with our lowest-attack ready minion
      auto ward_guard_it = std::find_if(guard_opponent_cards.begin(), guard_opponent_cards.end(),
         [](const Card& c) { return c.hasAbility(CardAbility::Ward); });

      if (ward_guard_it != guard_opponent_cards.end())
      {
         auto weakest_attacker = player_board_cards.end();
         int min_atk = 1000;
         for (auto it = player_board_cards.begin(); it != player_board_cards.end(); ++it)
         {
            if (it->getCanAttack() && it->getAttack() > 0 && it->getAttack() < min_atk)
            {
               min_atk = it->getAttack();
               weakest_attacker = it;
            }
         }

         if (weakest_attacker != player_board_cards.end())
         {
            int target_id = ward_guard_it->getId();
            std::cout << "ATTACK " << weakest_attacker->getId() << ' ' << target_id << ';';
            weakest_attacker->setCanAttack(false);

            auto opp_it = std::find_if(opponent_cards.begin(), opponent_cards.end(),
               [target_id](const Card& c) { return c.getId() == target_id; });
            if (opp_it != opponent_cards.end())
            {
               opp_it->takeDamage(weakest_attacker->getAttack(), weakest_attacker->hasAbility(CardAbility::Lethal));
               if (opp_it->getDefense() <= 0)
               {
                  opponent_cards.erase(opp_it);
               }
            }
            continue;
         }
      }

      // Find best attacker against remaining guards
      double best_guard_score = -1e9;
      auto best_att = player_board_cards.end();
      auto best_tgt = opponent_cards.end();

      for (auto att = player_board_cards.begin(); att != player_board_cards.end(); ++att)
      {
         if (!att->getCanAttack() || att->getAttack() <= 0) continue;

         for (auto tgt = opponent_cards.begin(); tgt != opponent_cards.end(); ++tgt)
         {
            if (!tgt->hasAbility(CardAbility::Guard)) continue;

            double score = att->attackProfit(*tgt);
            // Overkill penalty: prefer minimal overkill
            if (att->getAttack() >= tgt->getDefense())
            {
               int overkill = att->getAttack() - tgt->getDefense();
               score -= overkill * 0.5;
            }

            if (score > best_guard_score)
            {
               best_guard_score = score;
               best_att = att;
               best_tgt = tgt;
            }
         }
      }

      if (best_att == player_board_cards.end() || best_tgt == opponent_cards.end())
      {
         break;
      }

      int target_id = best_tgt->getId();
      std::cout << "ATTACK " << best_att->getId() << ' ' << target_id << ';';
      best_att->setCanAttack(false);

      best_tgt->takeDamage(best_att->getAttack(), best_att->hasAbility(CardAbility::Lethal));
      if (best_tgt->getDefense() <= 0)
      {
         opponent_cards.erase(best_tgt);
      }
   }

   // 4. No guards remain: choose between attacking face or taking high-value trades (free trade / trading up)
   for (auto& player_card : player_board_cards)
   {
      if (player_card.getAttack() <= 0 || !player_card.getCanAttack())
      {
         continue;
      }

      // Base face score
      double face_score = player_card.getAttack() * 50.0;
      if (opponent.getHealth() <= 12)
      {
         face_score += 2000.0;
      }
      else if (opponent.getHealth() <= 15)
      {
         face_score += (16 - opponent.getHealth()) * 40.0;
      }
      if (player_card.hasAbility(CardAbility::Drain))
      {
         face_score += player_card.getAttack() * 25.0;
      }

      double best_trade_score = -1e9;
      int best_target_id = -1;

      for (const auto& enemy : opponent_cards)
      {
         double trade_score = 0.0;
         if (enemy.hasAbility(CardAbility::Ward))
         {
            trade_score = 100.0 - player_card.getAttack() * 15.0;
         }
         else
         {
            bool kills_target = player_card.hasAbility(CardAbility::Lethal) || (player_card.getAttack() >= enemy.getDefense());
            bool survives = player_card.hasAbility(CardAbility::Ward) || (!enemy.hasAbility(CardAbility::Lethal) && enemy.getAttack() < player_card.getDefense());

            if (kills_target && survives)
            {
               // Free trade: friendly kills enemy and survives
               trade_score = 3500.0 + enemy.getAttack() * 45.0 + enemy.getDefense() * 25.0;
            }
            else if (kills_target && !survives)
            {
               // 1-for-1 mutual kill: only trade if enemy is higher value (trading up)
               double enemy_val = enemy.getAttack() * 1.5 + enemy.getDefense();
               double my_val = player_card.getAttack() * 1.5 + player_card.getDefense();
               if (enemy.hasAbility(CardAbility::Lethal)) enemy_val += 15.0;
               if (enemy.getAttack() >= 5) enemy_val += 12.0;

               if (enemy_val > my_val)
               {
                  trade_score = 1800.0 + (enemy_val - my_val) * 60.0;
               }
               else
               {
                  trade_score = 200.0 - (my_val - enemy_val) * 50.0;
               }
            }
            else
            {
               // Friendly dies without killing enemy: never do this
               trade_score = -1000.0;
            }
         }

         if (trade_score > best_trade_score)
         {
            best_trade_score = trade_score;
            best_target_id = enemy.getId();
         }
      }

      int attack_id = -1;
      if (best_trade_score > face_score)
      {
         attack_id = best_target_id;
      }

      std::cout << "ATTACK " << player_card.getId() << ' ' << attack_id << ';';
      player_card.setCanAttack(false);

      if (attack_id != -1)
      {
         auto attacked_opponent_card = std::find_if(opponent_cards.begin(), opponent_cards.end(),
            [attack_id](const Card& card) { return card.getId() == attack_id; });
         if (attacked_opponent_card != opponent_cards.end())
         {
            attacked_opponent_card->takeDamage(player_card.getAttack(), player_card.hasAbility(CardAbility::Lethal));
            if (attacked_opponent_card->getDefense() <= 0)
            {
               opponent_cards.erase(attacked_opponent_card);
            }
         }
      }
   }
   std::cout << "PASS" << std::endl;
}

double Dominator::getDraftCardRatio(const Card& card) const
{
   double score = 0.0;
   int cost = card.getCost();
   int cost_bucket = std::min(cost, 7);

   if (card.getType() == CardType::Creature)
   {
      double attack = card.getAttack();
      double defense = card.getDefense();
      score += attack * 1.15 + defense * 1.15;

      // Card draw is very powerful in LOCM
      score += card.getDraw() * 4.5;

      // Abilities
      if (card.hasAbility(CardAbility::Guard))
      {
         score += (m_guards_count < 5) ? 3.8 : 2.0;
      }
      if (card.hasAbility(CardAbility::Ward))
      {
         score += 3.8;
      }
      if (card.hasAbility(CardAbility::Lethal))
      {
         score += 2.8;
      }
      if (card.hasAbility(CardAbility::Charge))
      {
         score += 2.5;
      }
      if (card.hasAbility(CardAbility::Drain))
      {
         score += 1.5;
      }
      if (card.hasAbility(CardAbility::Breakthrough))
      {
         score += 1.0;
      }

      score += card.getPlayerHealthChange() * 0.25;
      score -= card.getOpponentHealthChange() * 0.6;

      if (attack == 0)
      {
         score -= 2.0;
      }
   }
   else if (card.getType() == CardType::GreenItem)
   {
      score += card.getAttack() * 1.0 + card.getDefense() * 1.1 + card.getDraw() * 4.2;
      if (card.hasAbility(CardAbility::Ward)) score += 3.2;
      if (card.hasAbility(CardAbility::Guard)) score += 2.0;
      if (card.hasAbility(CardAbility::Lethal)) score += 2.2;
      if (card.hasAbility(CardAbility::Charge)) score += 2.0;
      if (card.hasAbility(CardAbility::Drain)) score += 1.2;
      score -= 0.8; // requires friendly creature on board
   }
   else if (card.getType() == CardType::RedItem)
   {
      int dmg = -card.getDefense();
      score += dmg * 1.6;
      score += std::abs(card.getAttack()) * 0.6;
      score += card.getDraw() * 4.2;

      for (char ab : card.getAbilities())
      {
         if (ab == 'G') score += 1.5;
         if (ab == 'W') score += 2.0;
         if (ab == 'L') score += 1.5;
      }

      if (dmg == 0 && card.getAttack() == 0 && card.getDraw() == 0)
      {
         score = -10.0;
      }
   }
   else if (card.getType() == CardType::BlueItem)
   {
      int dmg = -card.getDefense();
      if (dmg > 0) score += dmg * 1.4;
      score -= card.getOpponentHealthChange() * 0.8;
      score += card.getPlayerHealthChange() * 0.25;
      score += card.getDraw() * 4.2;
   }

   // Mana cost efficiency: subtract cost scaling
   score -= cost * 1.85;

   // Item cap management (max 4-5 items in deck)
   if (card.getType() != CardType::Creature)
   {
      if (m_items_count >= 5)
      {
         score -= 8.0;
      }
      else if (m_items_count >= 3)
      {
         score -= 2.5;
      }
   }

   // Mana curve balancing
   // Target distribution: 0-1: 2, 2: 5, 3: 8, 4: 6, 5: 5, 6: 2, 7+: 2
   static const double ideal_curve[8] = { 2.0, 2.0, 5.0, 8.0, 6.0, 5.0, 2.0, 2.0 };
   double expected = ideal_curve[cost_bucket] * (std::max(1, m_pick_number) / 30.0);
   int current = m_draft_costs_cards[cost_bucket];

   if (current > expected + 1.0)
   {
      score -= (current - expected) * 1.8;
   }
   else if (current < expected - 0.5)
   {
      score += (expected - current) * 1.2;
   }

   if (current >= ideal_curve[cost_bucket])
   {
      score -= (current - ideal_curve[cost_bucket] + 1) * 2.5;
   }

   if (cost >= 7 && current >= 2)
   {
      score -= 5.0;
   }

   return score;
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
