#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

template <class T>
class Vector2
{
public:
   Vector2();
   Vector2(T x, T y);
   Vector2(Vector2 const& other);
   Vector2(T value);
   virtual ~Vector2();
   Vector2 operator+(const Vector2& rhs);
   Vector2 operator-(const Vector2& rhs);
   Vector2 operator*(T num);
   Vector2& operator+=(Vector2 const& rhs);
   Vector2& operator-=(Vector2 const& rhs);
   Vector2& operator*=(T num);
   T distance(const Vector2& other);
   Vector2 closest(const Vector2& first, const Vector2& second);

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
T Vector2<T>::distance(const Vector2& other)
{
   T dx = this->x - other.x;
   T dy = this->y - other.y;

   return std::sqrt(dx * dx + dy * dy);
}

template <class T>
Vector2<T> Vector2<T>::closest(const Vector2& first, const Vector2& second)
{
   T dist_first = this->distance(first);
   T dist_second = this->distance(second);

   return (dist_first < dist_second) ? first : second;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& vec)
{
   os << vec.x << ' ' << vec.y;

   return os;
}

template <class T>
std::istream& operator>>(std::istream& is, Vector2<T>& vec)
{
   is >> vec.x >> vec.y;

   return is;
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

struct Entity
{
   Vector2<int> position;
   std::string type; // WALL, ROOT, BASIC, TENTACLE, HARVESTER, SPORER, A, B, C, D
   int owner; // 1 if your organ, 0 if enemy organ, -1 if neither
   int organ_id; // id of this entity if it's an organ, 0 otherwise
   std::string organ_dir; // N,E,S,W or X if not an organ
   int organ_parent_id;
   int organ_root_id;
};

std::istream& operator>>(std::istream& is, Entity& entity)
{
   is >> entity.position >> entity.type >> entity.owner >> entity.organ_id >>
      entity.organ_dir >> entity.organ_parent_id >> entity.organ_root_id;
   return is;
}

enum class EntityType
{
   Wall = 0,
   Root,
   Basic,
   Tentacle,
   Harvester,
   Sporer,
   A,
   B,
   C,
   D,
   Unknown
};

int bfs_distance(const Vector2<int>& start, const Vector2<int>& goal, const std::vector<std::vector<EntityType>>& grid)
{
   if (start == goal) return 0;

   int width = grid[0].size();
   int height = grid.size();
   std::vector<std::vector<int>> dist(height, std::vector<int>(width, -1));
   std::queue<Vector2<int>> q;

   q.push(start);
   dist[start.y][start.x] = 0;

   const int dx[4] = {1, -1, 0, 0};
   const int dy[4] = {0, 0, 1, -1};

   while (!q.empty())
   {
      Vector2<int> cur = q.front();
      q.pop();

      for (int i = 0; i < 4; i++)
      {
         int nx = cur.x + dx[i];
         int ny = cur.y + dy[i];

         if (nx < 0 || ny < 0 || nx >= width || ny >= height)
            continue;
         
         if (grid[ny][nx] == EntityType::Wall || grid[ny][nx] == EntityType::Basic)
            continue;

         if (dist[ny][nx] != -1)
            continue;

         dist[ny][nx] = dist[cur.y][cur.x] + 1;
         if (nx == goal.x && ny == goal.y)
            return dist[ny][nx];

         q.push({nx, ny});
      }
   }

   return -1;
}

int main()
{
   int width; // columns in the game grid
   int height; // rows in the game grid
   std::cin >> width >> height; std::cin.ignore();

   // game loop
   while (1)
   {
      int entity_count;
      std::cin >> entity_count; std::cin.ignore();
      std::vector<Entity> my_organs;
      std::vector<Entity> A_proteins;
      std::vector<std::vector<EntityType>> grid(height, std::vector<EntityType>(width));
      for (int i = 0; i < entity_count; i++)
      {
         Entity entity;
         std::cin >> entity; std::cin.ignore();
         if (entity.type == "A")
         {
            A_proteins.push_back(entity);
         }
         else if (entity.owner == 1)
         {
            my_organs.push_back(entity);
         }

         if (entity.type == "WALL")
         {
            grid[entity.position.y][entity.position.x] = EntityType::Wall;
         }
         else if (entity.type == "ROOT")
         {
            grid[entity.position.y][entity.position.x] = EntityType::Root;
         }
         else if (entity.type == "BASIC")
         {
            grid[entity.position.y][entity.position.x] = EntityType::Basic;
         }
         else if (entity.type == "TENTACLE")
         {
            grid[entity.position.y][entity.position.x] = EntityType::Tentacle;
         }
         else if (entity.type == "HARVESTER")
         {
            grid[entity.position.y][entity.position.x] = EntityType::Harvester;
         }
         else if (entity.type == "SPORER")
         {
            grid[entity.position.y][entity.position.x] = EntityType::Sporer;
         }
         else if (entity.type == "A")
         {
            grid[entity.position.y][entity.position.x] = EntityType::A;
         }
         else if (entity.type == "B")
         {
            grid[entity.position.y][entity.position.x] = EntityType::B;
         }
         else if (entity.type == "C")
         {
            grid[entity.position.y][entity.position.x] = EntityType::C;
         }
         else if (entity.type == "D")
         {
            grid[entity.position.y][entity.position.x] = EntityType::D;
         }
         else
         {
            grid[entity.position.y][entity.position.x] = EntityType::Unknown;
         }
         
      }
      int my_a;
      int my_b;
      int my_c;
      int my_d; // your protein stock
      std::cin >> my_a >> my_b >> my_c >> my_d; std::cin.ignore();
      int opp_a;
      int opp_b;
      int opp_c;
      int opp_d; // opponent's protein stock
      std::cin >> opp_a >> opp_b >> opp_c >> opp_d; std::cin.ignore();
      int required_actions_count; // your number of organisms, output an action for each one in any order
      std::cin >> required_actions_count; std::cin.ignore();

      Entity closest_organ = my_organs[0];
      Entity closest_entity = A_proteins[0];
      for (Entity& my_organ : my_organs)
      {
         for (Entity& protein : A_proteins)
         {
            if (bfs_distance(my_organ.position, protein.position, grid) <
               bfs_distance(closest_organ.position, closest_entity.position, grid))
            {
               closest_organ = my_organ;
               closest_entity = protein;
            }
         }
      }
      for (int i = 0; i < required_actions_count; i++)
      {
         std::cout << "GROW " << closest_organ.organ_id << " " << closest_entity.position << " BASIC" << std::endl;
      }
   }
}