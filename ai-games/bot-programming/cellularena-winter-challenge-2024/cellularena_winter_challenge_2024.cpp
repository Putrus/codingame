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
   Empty = 0,
   Wall,
   Root,
   Basic,
   Tentacle,
   Harvester,
   Sporer,
   A,
   B,
   C,
   D
};

EntityType entityTypeFromString(const std::string& type_str)
{
   if (type_str == "WALL")
   {
      return EntityType::Wall;
   }
   else if (type_str == "ROOT")
   {
      return EntityType::Root;
   }
   else if (type_str == "BASIC")
   {
      return EntityType::Basic;
   }
   else if (type_str == "TENTACLE")
   {
      return EntityType::Tentacle;
   }
   else if (type_str == "HARVESTER")
   {
      return EntityType::Harvester;
   }
   else if (type_str == "SPORER")
   {
      return EntityType::Sporer;
   }
   else if (type_str == "A")
   {
      return EntityType::A;
   }
   else if (type_str == "B")
   {
      return EntityType::B;
   }
   else if (type_str == "C")
   {
      return EntityType::C;
   }
   else if (type_str == "D")
   {
      return EntityType::D;
   }
   else
   {
      return EntityType::Empty;
   }
}

int main()
{
   const std::vector<Vector2<int>> dirs = {
      {0, -1},
      {0,  1},
      {-1, 0},
      {1,  0}
   };
   int width; // columns in the game grid
   int height; // rows in the game grid
   std::cin >> width >> height; std::cin.ignore();
   bool harvester_grown = false;
   // game loop
   while (1)
   {
      int entity_count;
      std::cin >> entity_count; std::cin.ignore();
      std::vector<Entity> my_organs;
      std::vector<std::vector<EntityType>> grid(height, std::vector<EntityType>(width));
      for (int i = 0; i < entity_count; i++)
      {
         Entity entity;
         std::cin >> entity; std::cin.ignore();
         if (entity.owner == 1)
         {
            my_organs.push_back(entity);
         }

         grid[entity.position.y][entity.position.x] = entityTypeFromString(entity.type);
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

      Entity chosen_organ = my_organs[0];
      Vector2<int> target_position = {0, 0};
      std::string grow_type = "BASIC";
      Vector2<int> harvester_dir = {0, 0};
      bool found = false;
      for (Entity& my_organ : my_organs)
      {
         for (auto& d : dirs)
         {
            int nx = my_organ.position.x + d.x;
            int ny = my_organ.position.y + d.y;

            if (nx < 0 || nx >= width || ny < 0 || ny >= height)
               continue;

            if (grid[ny][nx] == EntityType::Empty)
            {
               bool near_A = false;
               
               for (auto& dd : dirs)
               {
                  int ax = nx + dd.x;
                  int ay = ny + dd.y;

                  if (ax < 0 || ax >= width || ay < 0 || ay >= height)
                     continue;

                  if (grid[ay][ax] == EntityType::A)
                  {
                     near_A = true;
                     harvester_dir = dd;
                     break;
                  }
               }

               if (near_A && !harvester_grown)
               {
                  chosen_organ = my_organ;
                  target_position = {nx, ny};
                  grow_type = "HARVESTER";
                  found = true;
                  break;
               }

               if (!found)
               {
                  chosen_organ = my_organ;
                  target_position = {nx, ny};
                  grow_type = "BASIC";
               }
            }
            if (found) break;
         }
      }
      for (int i = 0; i < required_actions_count; i++)
      {
         std::string direction = "N";
         if (harvester_dir.x == 1) direction = "E";
         else if (harvester_dir.x == -1) direction = "W";
         else if (harvester_dir.y == 1) direction = "S";
         std::cout << "GROW " << chosen_organ.organ_id << " " << target_position << " " << grow_type << " " << direction << std::endl;
         if (grow_type == "HARVESTER")
         {
            harvester_grown = true;
         }
      }
   }
}