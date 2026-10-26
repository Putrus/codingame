#include <iostream>
#include <string>
#include <cmath>
#include <vector>

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

struct Pellet
{
   Vector2<int> position;
   int value;
};

std::istream& operator>>(std::istream& is, Pellet& pellet)
{
   is >> pellet.position >> pellet.value;
   return is;
}

enum class PacType
{
   NEAREST = 0,
   FARTHEST,
   GREEDY,
   NONE
};

struct Pac
{
   int id;
   bool mine;
   Vector2<int> position;
   std::string type_id;
   int speed_turns_left;
   int ability_cooldown;
   PacType type;
};

std::istream& operator>>(std::istream& is, Pac& pac)
{
   is >> pac.id >> pac.mine >> pac.position >> pac.type_id >> pac.speed_turns_left >> pac.ability_cooldown;
   return is;
}

int main()
{
   int width; // size of the grid
   int height; // top left corner is (x=0, y=0)
   std::cin >> width >> height; std::cin.ignore();
   for (int i = 0; i < height; i++)
   {
      std::string row;
      std::getline(std::cin, row); // one line of the grid: space " " is floor, pound "#" is wall
   }

   // game loop
   while (1)
   {
      int my_score;
      int opponent_score;
      std::cin >> my_score >> opponent_score; std::cin.ignore();
      int visible_pac_count; // all your pacs and enemy pacs in sight
      std::cin >> visible_pac_count; std::cin.ignore();
      std::vector<Pac> mine_pacs;
      for (int i = 0; i < visible_pac_count; i++)
      {
         Pac pac;
         std::cin >> pac; std::cin.ignore();
         pac.type = static_cast<PacType>(pac.id % 3);
         if (pac.mine)
         {
            mine_pacs.push_back(pac);
         }
      }
      int visible_pellet_count; // all pellets in sight
      std::cin >> visible_pellet_count; std::cin.ignore();
      std::vector<Pellet> pellets;
      Pellet target{{width, height}, 0};
      int target_distance = std::numeric_limits<int>::max();
      for (int i = 0; i < visible_pellet_count; i++)
      {
         Pellet pellet;
         std::cin >> pellet; std::cin.ignore();
         pellets.push_back(pellet);
      }

      for (Pac& mine_pac : mine_pacs)
      {
         target = { {0, 0}, 0 };
         target_distance = std::numeric_limits<int>::max();
         for (Pellet& pellet : pellets)
         {
            int distance = mine_pac.position.distance(pellet.position);
            if (pellet.value > target.value || (pellet.value == target.value && distance < target_distance))
            {
               target = pellet;
               target_distance = distance;
            }
         }
         pellets.erase(std::remove_if(pellets.begin(), pellets.end(), [&target](const Pellet& pellet) {
            return pellet.position == target.position;
            }), pellets.end());
         std::cout << "MOVE " << mine_pac.id << " " << target.position << "|";
      }
      std::cout << std::endl;
   }
}