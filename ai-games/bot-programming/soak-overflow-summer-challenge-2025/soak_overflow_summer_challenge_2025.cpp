#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
namespace Utils
{
   namespace Math
   {
      template <class T>
      class Vector2
      {
      public:
         Vector2();
         Vector2(T x, T y);
         Vector2(Vector2 const& other);
         Vector2(T value);
         virtual ~Vector2();
         Vector2 operator+(Vector2 const& rhs);
         Vector2 operator-(Vector2 const& rhs);
         Vector2 operator*(T num);
         Vector2& operator+=(Vector2 const& rhs);
         Vector2& operator-=(Vector2 const& rhs);
         Vector2& operator*=(T num);
      public:
         T x;
         T y;
      };
      template <class T>
      Vector2<T>::Vector2() : x((T)0), y((T)0) {}
      template <class T>
      Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}
      
      template <class T>
      Vector2<T>::Vector2(const Vector2& other) : x(other.x), y(other.y) {}
      template <class T>
      Vector2<T>::Vector2(T value) : x(value), y(value) {}
      template <class T>
      Vector2<T>::~Vector2() {}
      template <class T>
      Vector2<T> Vector2<T>::operator+(Vector2 const& rhs)
      {
         return { this->x + rhs.x, this->y + rhs.y };
      }
      template <class T>
      Vector2<T> Vector2<T>::operator-(Vector2 const& rhs)
      {
         return { this->x - rhs.x, this->y - rhs.y };
      }
      template <class T>
      Vector2<T> Vector2<T>::operator*(T num)
      {
         return { this->x * num, this->y * num };
      }
      template <class T>
      Vector2<T>& Vector2<T>::operator+=(Vector2 const& rhs)
      {
         this->x += rhs.x;
         this->y += rhs.y;
         return *this;
      }
      template <class T>
      Vector2<T>& Vector2<T>::operator-=(Vector2 const& rhs)
      {
         this->x -= rhs.x;
         this->y -= rhs.y;
         return *this;
      }
      template <class T>
      Vector2<T>& Vector2<T>::operator*=(T num)
      {
         this->x *= num;
         this->y *= num;
         return *this;
      }
      template <class T>
      std::istream& operator>>(std::istream& is, Vector2<T>& rhs)
      {
         is >> rhs.x >> rhs.y;
         return is;
      }
      template <class T>
      std::ostream& operator<<(std::ostream& os, Vector2<T> const& rhs)
      {
         os << rhs.x << ' ' << rhs.y;
         return os;
      }
      template <class T>
      bool operator==(Vector2<T> const& lhs, Vector2<T> const& rhs)
      {
         return lhs.x == rhs.x && lhs.y == rhs.y;
      }
      template <class T>
      bool operator!=(Vector2<T> const& lhs, Vector2<T> const& rhs)
      {
         return lhs.x != rhs.x || lhs.y != rhs.y;
      }
      template <class T>
      bool operator!=(Vector2<T>& lhs, Vector2<T> & rhs)
      {
         return lhs.x != rhs.x || lhs.y != rhs.y;
      }
   }
}
enum class Tile : int
{
   Empty = 0,
   LowCover = 1,
   HighCover = 2
};
class Grid
{
public:
   std::vector<Tile>& operator[](int y);
   Tile& operator[](const Utils::Math::Vector2<int>& position);
   int height() const;
   int width() const;
   friend std::istream& operator>>(std::istream& is, Grid& grid);
private:
   std::vector<std::vector<Tile>> grid;
};
std::istream& operator>>(std::istream& is, Grid& grid);
std::vector<Tile>& Grid::operator[](int y)
{
   return grid.at(y);
}
Tile& Grid::operator[](const Utils::Math::Vector2<int>& position)
{
   return grid.at(position.y).at(position.x);
}
int Grid::height() const
{
   return static_cast<int>(grid.size());
}
int Grid::width() const
{
   if (grid.empty())
   {
      return 0;
   }
   return static_cast<int>(grid.at(0).size());
}
std::istream& operator>>(std::istream& is, Grid& grid)
{
   grid.grid.clear();
   int width, height;
   is >> width >> height;
   is.ignore();
   for (int i = 0; i < height; i++)
   {
      grid.grid.push_back(std::vector<Tile>(width, Tile::Empty));
      for (int j = 0; j < width; j++)
      {
         int x, y, tile;
         is >> x >> y >> tile;
         is.ignore();
         grid[y][x] = static_cast<Tile>(tile);
      }
   }
   return is;
}
class Agent
{
public:
   void update(int splash_bombs, int cooldown, int wetness, const Utils::Math::Vector2<int>& position);
   std::string action(const std::map<int, Agent>& enemies, const Grid& grid) const;
   friend std::istream& operator>>(std::istream& is, Agent& agent);
private:
   int shoot_cooldown = 0; //number of turns between each of this agent's shots
   int optimal_range = 0; //maximum manhattan distance for greatest damage output
   int soaking_power = 0; //damage output within optimal conditions
   int splash_bombs = 0; //number of splash bombs this can throw this game
   int cooldown = 0; //number of turns before this agent can shoot
   int wetness = 0; //damage (0-100) this agent has taken
   Utils::Math::Vector2<int> position = 0;
};
std::istream& operator>>(std::istream& is, Agent& agent);
void Agent::update(int splash_bombs, int cooldown, int wetness, const Utils::Math::Vector2<int>& position)
{
   this->splash_bombs = splash_bombs;
   this->cooldown = cooldown;
   this->wetness = wetness;
   this->position = position;
}
std::string Agent::action(const std::map<int, Agent>& enemies, const Grid& grid) const
{
   std::ostringstream action;
   if (cooldown != 0)
   {
      int y = std::rand() % grid.height();
      int x = std::rand() % grid.width();
      action << ";MOVE " << x << " " << y;
      return action.str();
   }
   for (const auto& enemy : enemies)
   {
      int distance = static_cast<int>(std::sqrt(std::pow(enemy.second.position.x - position.x, 2) +
         std::pow(enemy.second.position.y - position.y, 2)));
      if (distance <= optimal_range * 2)
      {
         action << ";MOVE " << enemy.second.position.x << " " << enemy.second.position.y << ";SHOOT " << enemy.first;
         if (splash_bombs > 0 && distance <= 3 &&
            (enemy.second.position.x == position.x || enemy.second.position.y == position.y))
         {
            action << ";THROW " << enemy.second.position.x << " " << enemy.second.position.y;
         }
         return action.str();
      }
   }
   if (action.str().empty())
   {
      int y = std::rand() % grid.height();
      int x = std::rand() % grid.width();
      action << ";MOVE " << x << " " << y;
   }
   return action.str();
}
std::istream& operator>>(std::istream& is, Agent& agent)
{
   is >> agent.shoot_cooldown >> agent.optimal_range >> agent.soaking_power >> agent.splash_bombs;
   return is;
}
class Player
{
public:
   Player();
   Player(int id);
   void addAgent(int id, const Agent& agent);
   void updateAgent(int id, int splash_bombs, int cooldown, int wetness, const Utils::Math::Vector2<int>& position);
   void removeDeadAgents(const std::set<int>& updated_agents);
   void makeAgentActions(Player& opponent, const Grid& grid);
   int getId() const;
   int getAgentNumber() const;
   friend std::istream& operator>>(std::istream& is, Player& player);
private:
   int id = -1;
   std::map<int, Agent> agents;
};
std::istream& operator>>(std::istream& is, Player& player);
Player::Player() {}
Player::Player(int id) : id(id) {}
void Player::addAgent(int id, const Agent& agent)
{
   agents.insert({ id, agent });
}
void Player::updateAgent(int id, int splash_bombs, int cooldown, int wetness, const Utils::Math::Vector2<int>& position)
{
   if (agents.find(id) == agents.end())
   {
      return;
   }
   agents.at(id).update(splash_bombs, cooldown, wetness, position);
}
void Player::removeDeadAgents(const std::set<int>& updated_agents)
{
   for (auto it = agents.begin(); it != agents.end(); )
   {
      if (updated_agents.find(it->first) == updated_agents.end())
      {
         it = agents.erase(it);
      }
      else
      {
         ++it;
      }
   }
}
void Player::makeAgentActions(Player& opponent, const Grid& grid)
{
   for (const auto& agent : agents)
   {
      std::cerr << "Action for agent " << agent.first << std::endl;
      std::cout << agent.first << agent.second.action(opponent.agents, grid) << std::endl;
   }
}
int Player::getId() const
{
   return id;
}
int Player::getAgentNumber() const
{
   return agents.size();
}
std::istream& operator>>(std::istream& is, Player& player)
{
   is >> player.id;
   return is;
}
class Game
{
public:
   Game();
   void run();
private:
   void initPlayers();
   void initAgents();
   void initGrid();
   void updateAgents();
   Player player;
   Player opponent;
   Grid grid;
};
Game::Game()
{
   initPlayers();
   initAgents();
   initGrid();
}
void Game::run()
{
   while (true)
   {
      updateAgents();
      player.makeAgentActions(opponent, grid);
   }
}
void Game::initPlayers()
{
   std::cin >> player;
   std::cin.ignore();
   opponent = Player((player.getId() == 0) ? 1 : 0);
}
void Game::initAgents()
{
   int agent_data_count; //total number of agents in the game
   std::cin >> agent_data_count;
   std::cin.ignore();
   for (int i = 0; i < agent_data_count; i++)
   {
      int agent_id; //unique identifier for this agent
      int owner_id; //player id of this agent
      Agent agent;
      std::cin >> agent_id >> owner_id >> agent;
      std::cin.ignore();
      if (owner_id == player.getId())
      {
         player.addAgent(agent_id, agent);
      }
      else
      {
         opponent.addAgent(agent_id, agent);
      }
   }
}
void Game::initGrid()
{
   std::cin >> grid;
}
void Game::updateAgents()
{
   int agent_count; //total number of agents still in the game
   std::cin >> agent_count;
   std::cin.ignore();
   std::set<int> updated_agents;
   for (int i = 0; i < agent_count; i++)
   {
      int agent_id;
      Utils::Math::Vector2<int> position;
      int x, y;
      int cooldown; //number of turns before this agent can shoot
      int splash_bombs;
      int wetness; //damage (0-100) this agent has taken
      std::cin >> agent_id >> position >> cooldown >> splash_bombs >> wetness;
      std::cin.ignore();
      player.updateAgent(agent_id, splash_bombs, cooldown, wetness, position);
      opponent.updateAgent(agent_id, splash_bombs, cooldown, wetness, position);
      updated_agents.insert(agent_id);
   }
   player.removeDeadAgents(updated_agents);
   opponent.removeDeadAgents(updated_agents);
   int player_agent_count; //number of alive agents controlled by you
   std::cin >> player_agent_count;
   std::cin.ignore();
   if (player.getAgentNumber() + opponent.getAgentNumber() != agent_count ||
      player.getAgentNumber() != player_agent_count)
   {
      std::cerr << "Error! Code data isn't equal game data!" << std::endl;
   }
}
int main()
{
   Game game;
   game.run();
   return 0;
}
